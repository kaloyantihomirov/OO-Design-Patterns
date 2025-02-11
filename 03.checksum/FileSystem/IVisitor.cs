namespace _03.checksum.FileSystem;

public interface IVisitor
{
    public void VisitFile(FileEntry file);
    public void VisitDirectory(DirectoryEntry directory);
}