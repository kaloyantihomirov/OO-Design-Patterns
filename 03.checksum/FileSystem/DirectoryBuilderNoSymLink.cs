namespace _03.checksum.FileSystem;

public class DirectoryBuilderNoSymLink : IAbstractDirectoryBuilder
{
    private DirectoryEntry? root;

    private Stack<DirectoryEntry> directoryStack = new Stack<DirectoryEntry>();

    private void AddDirectoryEntry(string directoryPath)
    {
        DirectoryEntry currentDirectory = directoryStack.Peek();
        DirectoryEntry subDir = new DirectoryEntry(directoryPath);
        currentDirectory.Add(subDir);
        directoryStack.Push(subDir);
    }

    public void StartDirectory(string directoryPath)
    {
        if (directoryStack.Count == 0)
        {
            root = new DirectoryEntry(directoryPath);
            directoryStack.Push(root);
        }
        else
        {
            AddDirectoryEntry(directoryPath);
        }
    }

    public void AddFileEntry(string filePath, long fileSize)
    {
        DirectoryEntry currentDirectory = directoryStack.Peek();
        currentDirectory.Add(new FileEntry(filePath, fileSize));
    }

    public void EndDirectory()
    {
        directoryStack.Pop();
    }

    public DirectoryEntry GetResult()
    {
        if (root == null)
        {
            throw new InvalidOperationException("No root directory");
        }

        return root;
    }
}