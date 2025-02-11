namespace _03.checksum.Checksum;

public class Sha1Calculator : IChecksumCalculator
{
    public string Calculate(Stream inputStream)
    {
        using var sha1 = System.Security.Cryptography.SHA1.Create();
        var hash = sha1.ComputeHash(inputStream);
        return BitConverter.ToString(hash).Replace("-", "").ToLowerInvariant();
    }
}