namespace _03.checksum.FileSystem;

public class SharedMemento
{
    private HashSet<string> visitedFiles;

    public HashSet<string> VisitedFiles
    {
        get => this.visitedFiles;
        set => this.visitedFiles = new HashSet<string>(value);
    }

    public long BytesProcessedSoFar { get; set; }

    public long BytesToProcess { get; set; }

    public long ElapsedMilliseconds { get; set; }
}