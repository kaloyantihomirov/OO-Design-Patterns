namespace _03.checksum.FileSystem;

public abstract class AbstractVisitor : IVisitor
{
    private bool executedBeforeDirectory = false;
    protected bool firstDirectory = true;

    protected HashSet<string> visitedFiles = new HashSet<string>();
    protected bool stopped = false;

    public void VisitFile(FileEntry file)
    {
        if (visitedFiles.Contains(file.GetPath())) return;

        visitedFiles.Add(file.GetPath());

        ProcessFile(file);
    }

    public abstract void ProcessFile(FileEntry file);

    public virtual void BeforeDirectoryTraversal() { }

    public virtual void AfterDirectoryTraversal() { }

    public virtual void VisitDirectory(DirectoryEntry directory)
    {
        if (stopped) return;

        bool wasFirst = firstDirectory;

        if (firstDirectory && !executedBeforeDirectory)
        {
            BeforeDirectoryTraversal();
            executedBeforeDirectory = true;
        }

        if (firstDirectory)
        {
            firstDirectory = false;
        }

        foreach (var child in directory.Children)
        {
            if (stopped) return;

            child.Accept(this);
        }

        if (wasFirst)
        {
            AfterDirectoryTraversal();
        }
    }
}