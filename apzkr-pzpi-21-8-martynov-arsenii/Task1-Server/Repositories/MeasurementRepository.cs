﻿using MongoDB.Driver;


public interface IMeasurementRepository
{
    Task<List<Measurement>> GetAllAsync();
    Task<Measurement> GetByIdAsync(string id);
    Task CreateAsync(Measurement measurement);
    Task UpdateAsync(string id, UpdateDefinition<Measurement> update);
    Task DeleteAsync(string id);
    Task<List<Measurement>> GetByDeviceIdAsync(string deviceId);
    Task<Measurement> GetLatestByTypeAsync(string deviceId, string measurementType);
}

public class MeasurementRepository : IMeasurementRepository
{
    private readonly IMongoCollection<Measurement> _collection;

    public MeasurementRepository(IMongoDatabase database)
    {
        _collection = database.GetCollection<Measurement>("Measurement");
    }

    public async Task<List<Measurement>> GetAllAsync()
    {
        return await _collection.Find(_ => true).ToListAsync();
    }

    public async Task<Measurement> GetByIdAsync(string id)
    {
        return await _collection.Find(Builders<Measurement>.Filter.Eq("Id", id)).FirstOrDefaultAsync();
    }

    public async Task<List<Measurement>> GetByDeviceIdAsync(string deviceId)
    {
        return await _collection.Find(Builders<Measurement>.Filter.Eq(m => m.DeviceId, deviceId)).ToListAsync();
    }

    public async Task<Measurement> GetLatestByTypeAsync(string deviceId, string measurementType)
    {
        return await _collection.Find(Builders<Measurement>.Filter.And(
            Builders<Measurement>.Filter.Eq(m => m.DeviceId, deviceId),
            Builders<Measurement>.Filter.Eq(m => m.MeasurementType, measurementType)))
            .SortByDescending(m => m.Timestamp)
            .FirstOrDefaultAsync();
    }

    public async Task<List<string>> GetAllDeviceIdsAsync()
    {
        return await _collection.Distinct<string>("DeviceId", Builders<Measurement>.Filter.Empty).ToListAsync();
    }

    public async Task CreateAsync(Measurement measurement)
    {
        await _collection.InsertOneAsync(measurement);
    }

    public async Task UpdateAsync(string id, UpdateDefinition<Measurement> update)
    {
        await _collection.UpdateOneAsync(Builders<Measurement>.Filter.Eq("Id", id), update);
    }

    public async Task DeleteAsync(string id)
    {
        await _collection.DeleteOneAsync(Builders<Measurement>.Filter.Eq("Id", id));
    }
}
