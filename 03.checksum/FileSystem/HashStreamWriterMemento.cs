namespace _03.checksum.FileSystem;

public class HashStreamWriterMemento
{
    public HashStreamWriterMemento(HashSet<string> visitedFiles)
    {
        this.VisitedFiles = new HashSet<string>(visitedFiles);
    }

    public HashSet<string> VisitedFiles { get; }
}