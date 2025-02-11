using _03.checksum.Checksum;

namespace _03.checksum.FileSystem;

public class HashStreamWriter : AbstractVisitor
{
    private readonly IChecksumCalculator checksumCalculator;
    private readonly Stream outputStream;

    HashStreamWriter(IChecksumCalculator checksumCalculator, 
        Stream outputStream)
    {
        this.checksumCalculator = checksumCalculator;
        this.outputStream = outputStream;
    }

    public override void ProcessFile(FileEntry file)
    {
        using FileStream fs = new FileStream(
            file.GetPath(),
            FileMode.Open,
            FileAccess.Read,
            FileShare.Read
        );

        string hashHex = checksumCalculator.Calculate(fs);

        using StreamWriter writer = new StreamWriter(outputStream, leaveOpen: true);
        writer.WriteLine($"{hashHex}  {file.GetPath()}");
        writer.Flush();
    }

}