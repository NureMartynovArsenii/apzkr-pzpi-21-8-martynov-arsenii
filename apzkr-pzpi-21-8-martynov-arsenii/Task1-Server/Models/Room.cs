using MongoDB.Bson.Serialization.Attributes;
using MongoDB.Bson;

public class Room
{
    [BsonId] 
    [BsonRepresentation(BsonType.ObjectId)] 
    public string Id { get; set; }
    public string RoomNumber { get; set; }
    public string Capacity { get; set; }
    public string GardenId { get; set; }
    [BsonIgnore]
    public string GardenName { get; set; }
}
