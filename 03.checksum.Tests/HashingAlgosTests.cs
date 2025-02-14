using Xunit;
using System.Text;
using _03.checksum.Checksum;

namespace _03.checksum.Tests;

public class Md5CalculatorTests
{
    [Theory]
    [InlineData("hello world", "5eb63bbbe01eeed093cb22bb8f5acdc3")]
    [InlineData("abc", "900150983cd24fb0d6963f7d28e17f72")]
    [InlineData("test string", "6f8db599de986fab7a21625b7916589c")]
    public void Calculate_ReturnsExpectedMd5Hash(string input, string expectedHash)
    {
        byte[] byteArray = Encoding.UTF8.GetBytes(input);
        using var stream = new MemoryStream(byteArray);
        var calculator = new Md5Calculator();

        string actual = calculator.Calculate(stream);

        Assert.Equal(expectedHash, actual);
    }
}

public class Sha1CalculatorTests
{
    [Theory]
    [InlineData("hello world", "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed")]
    [InlineData("abc", "a9993e364706816aba3e25717850c26c9cd0d89d")]
    [InlineData("test string", "661295c9cbf9d6b2f6428414504a8deed3020641")]
    public void Calculate_ReturnsExpectedSha1Hash(string input, string expectedHash)
    {
        byte[] byteArray = Encoding.UTF8.GetBytes(input);
        using var stream = new MemoryStream(byteArray);
        var calculator = new Sha1Calculator();

        string actual = calculator.Calculate(stream);

        Assert.Equal(expectedHash, actual);
    }
}
