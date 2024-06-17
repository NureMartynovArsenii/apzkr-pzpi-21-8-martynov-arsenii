//using Lb2.Repositories;
using MongoDB.Driver;

public interface IGardenService
{
    Task<List<Garden>> GetAllAsync();
    Task<Garden> GetByIdAsync(string id);
    Task CreateAsync(GardenCreateModel gardenCreateModel);
    Task UpdateAsync(string id, GardenUpdateModel updateModel);
    Task DeleteAsync(string id);
    Task<Garden> GetGardenByUserIdAsync(string userId);
}

public class GardenService : IGardenService
{
    private readonly IGardenRepository _gardenRepository;
    private readonly IMongoCollection<Garden> _gardens;
    public GardenService(IGardenRepository gardenRepository, IMongoDatabase database)
    {
        _gardenRepository = gardenRepository;
        _gardens = database.GetCollection<Garden>("Gardens");
    }

    public async Task<List<Garden>> GetAllAsync()
    {
        return await _gardenRepository.GetAllAsync();
    }

    public async Task<Garden> GetByIdAsync(string id)
    {
        return await _gardenRepository.GetByIdAsync(id);
    }
    public async Task<Garden> GetGardenByUserIdAsync(string userId)
    {
        return await _gardenRepository.GetGardenByUserIdAsync(userId);
    }
    public async Task CreateAsync(GardenCreateModel gardenCreateModel)
    {
        var garden = new Garden
        {
            Name = gardenCreateModel.Name,
            Location = gardenCreateModel.Location,
            Director = gardenCreateModel.Director,
            Email = gardenCreateModel.Email,
            Phone = gardenCreateModel.Phone,
            Users = gardenCreateModel.Users
        };
        await _gardenRepository.CreateAsync(garden);
    }
    public async Task UpdateAsync(string id, GardenUpdateModel updateModel)
    {
        var garden = await _gardenRepository.GetByIdAsync(id);
        if (garden == null)
        {
            throw new Exception("Garden not found");
        }

        
        var updatedUsers = garden.Users.Concat(updateModel.Users.Where(u => !garden.Users.Any(existingUser => existingUser.Id == u.Id))).ToList();

        var update = Builders<Garden>.Update
            .Set(g => g.Name, updateModel.Name)
            .Set(g => g.Location, updateModel.Location)
            .Set(g => g.Director, updateModel.Director)
            .Set(g => g.Email, updateModel.Email)
            .Set(g => g.Phone, updateModel.Phone)
            .Set(g => g.Users, updatedUsers);

        await _gardenRepository.UpdateAsync(id, update);
    }

    public async Task DeleteAsync(string id)
    {
        await _gardenRepository.DeleteAsync(id);
    }
}


