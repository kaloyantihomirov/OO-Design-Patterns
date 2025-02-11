using System.Runtime.InteropServices;

namespace _03.checksum.FileSystem;

/* Няколко забележки:
 * Не можах да постигна с Windows 10 пряк път към друг пряк път. Автоматично вторият пряк
 * път започва да сочи към целта на първия. Решението НЕ разчита на тази особеност.
 * От това, което прочетох в интернет, при по-старите ОС това е било възможно.
 * Тествах решението си чрез symlink-ове в Windows 10 и работи коректно, поне за основните
 * случаи (symlink към symlink, symlink към пряк път, циклични symlink зависимости,
 * пряк път към вече обработена директория или вече обработен файл).
 * Исках да използвам адаптацията на Builder шаблона от Head First Design Patterns книгата,
 * която разчита на push методология за получаване необходимата информация за строене на
 * съответния обект (Composite в случая). Това обаче се оказа не много чисто за този builder;
 * за стандартния, който не "разбира" symlink-ове, се получи добре.
 * Идеята ми беше да отстраня знанието за файловата система от Builder-a, като някой да влива
 * това знание в него, но не измислих начин да го направя, и то ефективно.
 */

public class SymLinkAwareDirectoryBuilder : IAbstractDirectoryBuilder
{
    private DirectoryEntry? root;
    private readonly Stack<DirectoryEntry> directoryStack = new Stack<DirectoryEntry>();
    private readonly HashSet<string> visitedPaths = new HashSet<string>(
        StringComparer.OrdinalIgnoreCase);

    private void AddDirectoryEntry(string directoryPath)
    {
        var currentDirectory = directoryStack.Peek();

        if (visitedPaths.Contains(directoryPath))
            return;

        var subDir = new DirectoryEntry(directoryPath);
        currentDirectory.Add(subDir);
        visitedPaths.Add(directoryPath);
        directoryStack.Push(subDir);
    }

    private string? ResolveTargetPath(string originalPath)
    {
        var visitedChain = new HashSet<string>(StringComparer.OrdinalIgnoreCase);

        string currentPath = Path.GetFullPath(originalPath);

        while (true)
        {
            if (visitedChain.Contains(currentPath) || visitedPaths.Contains(currentPath))
            {
                return null;
            }
            visitedChain.Add(currentPath);

            FileInfo fi = new FileInfo(currentPath);
            if (!string.IsNullOrEmpty(fi.LinkTarget))
            {
                string linkTargetFull = Path.GetFullPath(fi.LinkTarget, Path.GetDirectoryName(currentPath)!);

                currentPath = linkTargetFull;
                continue;
            }

            //TODO: Delegate the responsibility for checkin if a file is a link  to 
            //ShortcutHelper class
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows)
                && fi.Extension.Equals(".lnk", StringComparison.OrdinalIgnoreCase))
            {
                string? lnkTarget = ShortcutHelper.GetLnkTarget(currentPath);
                if (!string.IsNullOrEmpty(lnkTarget))
                {
                    string linkTargetFull = Path.GetFullPath(lnkTarget, Path.GetDirectoryName(currentPath)!);
                    currentPath = linkTargetFull;
                    continue;
                }
            }

            break;
        }

        return currentPath;
    }

    private void ProcessDirectory()
    {
        DirectoryEntry currentDirectory = directoryStack.Peek();

        foreach (var file in Directory.GetFiles(currentDirectory.GetPath()))
        {
            ProcessFileEntry(file);
        }

        foreach (var subdirectory in Directory.GetDirectories(currentDirectory.GetPath()))
        {
            StartDirectory(subdirectory);
        }

        EndDirectory();
    }

    private void ProcessFileEntry(string filePath)
    {
        string? resolvedPath = ResolveTargetPath(filePath);

        if(resolvedPath == null)
        {
            //long fileSize = 0;

            //if (File.Exists(filePath))
            //{
            //    FileInfo fi = new FileInfo(filePath);
            //    fileSize = fi.Length;
            //}

            //AddFileEntry(filePath, fileSize);
            AddFileEntry(filePath, 0);
        }
        else if (Directory.Exists(resolvedPath))
        {
            AddDirectoryEntry(resolvedPath);
            ProcessDirectory();
        }
        else if (File.Exists(resolvedPath))
        {
            long fileSize = new FileInfo(resolvedPath).Length;
            AddFileEntry(resolvedPath, fileSize);
        }
    }

    public void StartDirectory(string directoryPath)
    {
        if (root == null)
        {
            string realDirPath = ResolveTargetPath(directoryPath);

            if (File.Exists(realDirPath))
            {
                throw new InvalidOperationException(
                    "Cannot start a directory with a file path.");
            }

            root = new DirectoryEntry(realDirPath);
            directoryStack.Push(root);

            visitedPaths.Add(realDirPath);
        }
        else
        {
            AddDirectoryEntry(directoryPath);
        }

        ProcessDirectory();
    }

    public void AddFileEntry(string filePath, long fileSize)
    {
        DirectoryEntry currentDirectory = directoryStack.Peek();
        currentDirectory.Add(new FileEntry(filePath, fileSize));
    }

    public void EndDirectory()
    {
        if (directoryStack.Count > 0)
        {
            directoryStack.Pop();
        }
    }

    public DirectoryEntry GetResult()
    {
        if (root == null)
        {
            throw new InvalidOperationException("No root directory started.");
        }

        return root;
    }

}
