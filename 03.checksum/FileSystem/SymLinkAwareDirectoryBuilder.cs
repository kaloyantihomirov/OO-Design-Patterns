using System.Runtime.InteropServices;

namespace _03.checksum.FileSystem;

public class SymLinkAwareDirectoryBuilder : IAbstractDirectoryBuilder
{
    private DirectoryEntry? root;
    private readonly Stack<DirectoryEntry> directoryStack = new Stack<DirectoryEntry>();

    // Tracks real paths (fully resolved) that have been visited 
    private readonly HashSet<string> visitedPaths = new HashSet<string>(
        StringComparer.OrdinalIgnoreCase);

    private void processDirectory()
    {
        DirectoryEntry currentDirectory = directoryStack.Peek();

        foreach (var file in Directory.GetFiles(currentDirectory.GetPath()))
        {
            processFileEntry(file);
        }

        foreach (var subdirectory in Directory.GetDirectories(currentDirectory.GetPath()))
        {
            StartDirectory(subdirectory);
        }

        EndDirectory();
    }

    private void processFileEntry(string filePath)
    {
        string resolvedPath = ResolveTargetPath(filePath);

        if (Directory.Exists(resolvedPath))
        {
            AddDirectoryEntry(resolvedPath);
            processDirectory();
        }
        else if (File.Exists(resolvedPath))
        {
            long fileSize = new FileInfo(resolvedPath).Length;
            AddFileEntry(resolvedPath, fileSize);
        }
        else
        {
            // Broken link or could not resolve => add as a file entry
            AddFileEntry(filePath, 0);
        }
    }

    public void StartDirectory(string directoryPath)
    {
        if (root == null)
        {
            // Resolve the directory to its real path in case it is itself a symlink
            string realDirPath = ResolveTargetPath(directoryPath);

            if (File.Exists(realDirPath))
            {
                throw new InvalidOperationException(
                    "Cannot start a directory with a file path.");
            }

            // First directory being added => treat as root
            root = new DirectoryEntry(realDirPath);
            directoryStack.Push(root);

            // Mark this real path visited (so we don't revisit if symlink points here)
            visitedPaths.Add(realDirPath);
        }
        else
        {
            AddDirectoryEntry(directoryPath);
        }

        processDirectory();
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

    private void AddDirectoryEntry(string directoryPath)
    {
        var currentDirectory = directoryStack.Peek();

        // If it’s already visited, skip
        if (visitedPaths.Contains(directoryPath))
            return;

        var subDir = new DirectoryEntry(directoryPath);
        currentDirectory.Add(subDir);

        visitedPaths.Add(directoryPath);
        directoryStack.Push(subDir);
    }

    /// <summary>
    /// Resolve target path by:
    /// 1) Checking if it's a real symlink (.NET's FileInfo.LinkTarget)
    /// 2) If on Windows, checking if it's a .lnk
    /// 3) Repeating the process until we reach a non-symlink or detect a cycle
    /// 
    /// Returns null if the link is broken.
    /// </summary>
    private string? ResolveTargetPath(string originalPath)
    {
        var visitedChain = new HashSet<string>(StringComparer.OrdinalIgnoreCase);

        string currentPath = Path.GetFullPath(originalPath);

        // Repeatedly chase symlinks or .lnk on Windows
        while (true)
        {
            // 1) If we've visited this path in *this chain of resolution*, it's a cycle
            if (visitedChain.Contains(currentPath))
            {
                // Cycle detected => return null or handle specially
                return null;
            }
            visitedChain.Add(currentPath);

            // 2) Check if it’s a real symlink (FileInfo.LinkTarget)
            FileInfo fi = new FileInfo(currentPath);
            if (!string.IsNullOrEmpty(fi.LinkTarget))
            {
                // It's a symlink. Resolve it
                string linkTargetFull = Path.GetFullPath(fi.LinkTarget, Path.GetDirectoryName(currentPath)!);

                // Move on to the next iteration to test the new path
                currentPath = linkTargetFull;
                continue;
            }

            // 3) Check if we are on Windows and it's a .lnk
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

            // If we reach here, currentPath is no longer a symlink or .lnk
            // or we couldn't resolve further => so this is our final real path
            break;
        }

        return currentPath;
    }
}
