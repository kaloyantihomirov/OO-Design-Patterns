namespace _03.checksum.FileSystem;

public class ReportWriter : AbstractVisitor
{
    private readonly Stream outputStream;

    public ReportWriter(Stream outputStream)
    {
        this.outputStream = outputStream;
    }

    public override void ProcessFile(FileEntry file)
    {
        using StreamWriter writer = new StreamWriter(outputStream, leaveOpen: true);
        writer.WriteLine($"{file.GetPath()} ({file.GetSizeInBytes()} bytes)");
        writer.Flush();
    }
}