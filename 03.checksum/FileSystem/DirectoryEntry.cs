namespace _03.checksum.FileSystem;

public class DirectoryEntry : FileSystemEntry
{
    private IList<FileSystemEntry> fileSystemEntries;
    private string directoryPath;
    private long? size;

    public DirectoryEntry(string directoryPath)
    {
        fileSystemEntries = new List<FileSystemEntry>();

        this.directoryPath = directoryPath;
    }

    public override void Add(FileSystemEntry fse)
    {
        fileSystemEntries.Add(fse);
    }

    public override void Remove(FileSystemEntry fse)
    {
        fileSystemEntries.Remove(fse);
    }

    public override FileSystemEntry GetChild(int i)
    {
        return fileSystemEntries[i];
    }

    public override string GetPath()
    {
        return directoryPath;
    }

    public override long GetSizeInBytes()
    {
        if (size != null)
        {
            return (long)size;
        }

        long res = 0;

        foreach (var fse in fileSystemEntries)
        {
            res += fse.GetSizeInBytes();
        }

        return (long)(size = res);
    }

    public override void Print()
    {
        Console.WriteLine($"{directoryPath} ({GetSizeInBytes()} bytes)");
        foreach (var fse in fileSystemEntries)
        {
            Console.Write(" ");
            fse.Print();
        }
    }

    public IEnumerable<FileSystemEntry> Children => fileSystemEntries;

    public override void Accept(IVisitor visitor)
    {
        visitor.VisitDirectory(this);
    }
}