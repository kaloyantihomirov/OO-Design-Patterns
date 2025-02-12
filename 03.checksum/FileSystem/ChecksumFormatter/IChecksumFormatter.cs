namespace _03.checksum.FileSystem.ChecksumFormatter;

public interface IChecksumFormatter
{
    void StartReport(StreamWriter sw);

    void WriteItem(StreamWriter sw, FileMetadata metadata);

    void EndReport(StreamWriter sw);
}

public record FileMetadata(
    string Path,
    long Size,
    string Checksum,
    bool IsBinaryMode);