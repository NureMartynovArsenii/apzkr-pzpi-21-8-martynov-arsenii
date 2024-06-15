using MongoDB.Driver;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson.Serialization.Attributes;
using MongoDB.Bson;
using Microsoft.AspNetCore.Authorization;
using MongoDB.Bson.IO;


[Route("api/[controller]")]
[ApiController]
public class BackupController : ControllerBase
{
    private readonly IMongoClient _mongoClient;

    public BackupController(IMongoClient mongoClient)
    {
        _mongoClient = mongoClient;
    }

    [HttpPost("CreateBackup")]
    public async Task<IActionResult> CreateBackup([FromBody] BackupRequest backupRequest)
    {
        var backupDirectory = backupRequest.BackupDirectory;
        var timestamp = DateTime.UtcNow.ToString("yyyyMMddHHmmss");
        var backupFolder = Path.Combine(backupDirectory, $"Backup_{timestamp}");

        if (!Directory.Exists(backupFolder))
        {
            Directory.CreateDirectory(backupFolder);
        }

        try
        {
            var db = _mongoClient.GetDatabase("ChildClimaCare");
            var collections = await db.ListCollectionNamesAsync();
            await collections.ForEachAsync(async collectionName =>
            {
                var collection = db.GetCollection<BsonDocument>(collectionName);
                var documents = await collection.Find(new BsonDocument()).ToListAsync();
                var backupFilePath = Path.Combine(backupFolder, $"ChildClimaCare_{collectionName}.json");

                await System.IO.File.WriteAllTextAsync(backupFilePath, documents.ToJson(new JsonWriterSettings { Indent = true }));
            });

            return Ok($"Резервне копіювання бази даних ChildClimaCare створено в {backupFolder}");
        }
        catch (Exception ex)
        {
            return StatusCode(500, $"Помилка при створенні резервної копії: {ex.Message}");
        }
    }
}

public class BackupRequest
{
    public string BackupDirectory { get; set; }
}
