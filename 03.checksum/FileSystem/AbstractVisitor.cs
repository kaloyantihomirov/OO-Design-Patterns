namespace _03.checksum.FileSystem;

public abstract class AbstractVisitor : IVisitor
{
    public void VisitFile(FileEntry file)
    {
        ProcessFile(file);
    }

    public abstract void ProcessFile(FileEntry file);

    public virtual void VisitDirectory(DirectoryEntry directory)
    {
        foreach (var child in directory.Children)
        {
            child.Accept(this);
        }
    }
}