namespace _03.checksum.FileSystem;

public abstract class AbstractVisitor : IVisitor
{
    private bool firstDirectory = true;

    public void VisitFile(FileEntry file)
    {
        ProcessFile(file);
    }

    public abstract void ProcessFile(FileEntry file);

    public virtual void BeforeDirectoryTraversal() { }

    public virtual void AfterDirectoryTraversal() { }

    public virtual void VisitDirectory(DirectoryEntry directory)
    {
        bool wasFirst = firstDirectory;

        if (firstDirectory)
        {
            BeforeDirectoryTraversal();
            firstDirectory = false;
        }

        foreach (var child in directory.Children)
        {
            child.Accept(this);
        }

        if (wasFirst)
        {
            AfterDirectoryTraversal();
        }
    }
}