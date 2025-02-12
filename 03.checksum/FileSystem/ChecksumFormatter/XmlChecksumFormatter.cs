namespace _03.checksum.FileSystem.ChecksumFormatter;

public class XmlChecksumFormatter : IChecksumFormatter
{
    public void StartReport(StreamWriter sw)
    {
        sw.WriteLine("<checksums>");
    }

    public void WriteItem(StreamWriter sw, FileMetadata metadata)
    {
        sw.WriteLine("  <item>");
        sw.WriteLine($"    <mode>{ (metadata.IsBinaryMode ? "binary" : "text") }</mode>");
        sw.WriteLine($"    <checksum>{metadata.Checksum}</checksum>");
        sw.WriteLine($"    <path>{metadata.Path}</path>");
        sw.WriteLine($"    <size>{metadata.Size}</size>");
        sw.WriteLine("  </item>");
    }

    public void EndReport(StreamWriter sw)
    {
        sw.WriteLine("</checksums>");
    }
}