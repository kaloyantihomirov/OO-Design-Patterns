namespace _03.checksum.Checksum;

public class Md5Calculator : IChecksumCalculator
{
    public string Calculate(Stream inputStream)
    {
        using var md5 = System.Security.Cryptography.MD5.Create();
        var hash = md5.ComputeHash(inputStream);
        return BitConverter.ToString(hash).Replace("-", "").ToLowerInvariant();
    }
}