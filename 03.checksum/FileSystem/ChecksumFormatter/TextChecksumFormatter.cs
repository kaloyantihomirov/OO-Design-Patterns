namespace _03.checksum.FileSystem.ChecksumFormatter;

public class TextChecksumFormatter : IChecksumFormatter
{
    public void StartReport(StreamWriter sw)
    {
    }

    public void WriteItem(StreamWriter sw, FileMetadata metadata)
    {
        char modeIndicator = metadata.IsBinaryMode ? '*' : ' ';

        sw.WriteLine($"{metadata.Checksum} {modeIndicator}{metadata.Path}");
    }

    public void EndReport(StreamWriter sw)
    {
    }
}

