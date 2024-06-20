using System.Collections.Concurrent;
using System.Globalization;
using MongoDB.Driver;

public interface IMeasurementService
{
    Task<List<Measurement>> GetAllAsync();
    Task<Measurement> GetByIdAsync(string id);
    Task CreateAsync(MeasurementCreateModel measurementCreateModel);
    Task<Measurement> CreateAndGetAsync(MeasurementCreateModel measurementCreateModel);
    Task UpdateAsync(string id, MeasurementUpdateModel updateModel);
    Task DeleteAsync(string id);
    Task<List<Measurement>> GetByDeviceIdAsync(string deviceId);
    Task CalculateAndStoreDerivedMetrics(string deviceId);
    void StartMeasurement();
    void StopMeasurement();
    bool IsMeasuring();
}

public class MeasurementService : IMeasurementService
{
    private readonly IMeasurementRepository _measurementRepository;
    private static bool _isMeasuring;

    public MeasurementService(IMeasurementRepository measurementRepository)
    {
        _measurementRepository = measurementRepository;
    }

    public async Task<List<Measurement>> GetAllAsync()
    {
        return await _measurementRepository.GetAllAsync();
    }

    public async Task<Measurement> GetByIdAsync(string id)
    {
        return await _measurementRepository.GetByIdAsync(id);
    }

    public async Task<List<Measurement>> GetByDeviceIdAsync(string deviceId)
    {
        return await _measurementRepository.GetByDeviceIdAsync(deviceId);
    }

    public async Task<Measurement> CreateAndGetAsync(MeasurementCreateModel measurementCreateModel)
    {
        var measurement = new Measurement
        {
            DeviceId = measurementCreateModel.DeviceId,
            MeasurementType = measurementCreateModel.MeasurementType,
            Value = measurementCreateModel.Value,
            Timestamp = DateTime.UtcNow
        };
        await _measurementRepository.CreateAsync(measurement);

        await CalculateAndStoreDerivedMetrics(measurement.DeviceId);

        return measurement;
    }

    public async Task CreateAsync(MeasurementCreateModel measurementCreateModel)
    {
        var measurement = new Measurement
        {
            DeviceId = measurementCreateModel.DeviceId,
            MeasurementType = measurementCreateModel.MeasurementType,
            Value = measurementCreateModel.Value,
            Timestamp = DateTime.UtcNow
        };
        await _measurementRepository.CreateAsync(measurement);

        await CalculateAndStoreDerivedMetrics(measurement.DeviceId);
    }

    public async Task UpdateAsync(string id, MeasurementUpdateModel updateModel)
    {
        var update = Builders<Measurement>.Update
            .Set(m => m.DeviceId, updateModel.DeviceId)
            .Set(m => m.MeasurementType, updateModel.MeasurementType)
            .Set(m => m.Value, updateModel.Value)
            .Set(m => m.Timestamp, DateTime.UtcNow);
        await _measurementRepository.UpdateAsync(id, update);

        var updatedMeasurement = new Measurement
        {
            Id = id,
            DeviceId = updateModel.DeviceId,
            MeasurementType = updateModel.MeasurementType,
            Value = updateModel.Value,
            Timestamp = DateTime.UtcNow
        };

        await CalculateAndStoreDerivedMetrics(updatedMeasurement.DeviceId);
    }

    public async Task DeleteAsync(string id)
    {
        await _measurementRepository.DeleteAsync(id);
    }

    public async Task CalculateAndStoreDerivedMetrics(string deviceId)
    {
        var latestTemperature = await _measurementRepository.GetLatestByTypeAsync(deviceId, "Temperature");
        var latestHumidity = await _measurementRepository.GetLatestByTypeAsync(deviceId, "Humidity");

        if (latestTemperature != null && latestHumidity != null)
        {
            Console.WriteLine($"Latest Temperature: {latestTemperature.Value}, Latest Humidity: {latestHumidity.Value}");

            if (double.TryParse(latestTemperature.Value, NumberStyles.Any, CultureInfo.InvariantCulture, out double temperature) &&
                double.TryParse(latestHumidity.Value, NumberStyles.Any, CultureInfo.InvariantCulture, out double humidity))
            {
                double heatIndex = CalculateHeatIndex(temperature, humidity);
                double dewPoint = CalculateDewPoint(temperature, humidity);

                await _measurementRepository.CreateAsync(new Measurement
                {
                    DeviceId = deviceId,
                    MeasurementType = "HeatIndex",
                    Value = heatIndex.ToString(CultureInfo.InvariantCulture),
                    Timestamp = DateTime.UtcNow
                });

                await _measurementRepository.CreateAsync(new Measurement
                {
                    DeviceId = deviceId,
                    MeasurementType = "DewPoint",
                    Value = dewPoint.ToString(CultureInfo.InvariantCulture),
                    Timestamp = DateTime.UtcNow
                });
            }
            else
            {
                throw new FormatException("Temperature or Humidity value format is invalid.");
            }
        }
    }
    //Business logic
    // Calculate Humidex based on temperature and humidity
    private double CalculateHeatIndex(double temperature, double humidity)
    {
        
        
        double dewPoint = CalculateDewPoint(temperature, humidity);
        // Humidex
        double e = 6.11 * Math.Exp(5417.7530 * ((1 / 273.16) - (1 / (dewPoint + 273.15))));
        double h = 0.5555 * (e - 10.0);
        double humidex = temperature + h;

        return humidex;
    }
    // Calculate Dew Point based on temperature and humidity
    private double CalculateDewPoint(double temperature, double humidity)
    {
        double a = 17.27;
        double b = 237.7;
        double alpha = ((a * temperature) / (b + temperature)) + Math.Log(humidity / 100.0);
        return (b * alpha) / (a - alpha);
    }

    public void StartMeasurement()
    {
        _isMeasuring = true;
        Console.WriteLine("Measurement started. _isMeasuring is now " + _isMeasuring);
    }

    public void StopMeasurement()
    {
        _isMeasuring = false;
        Console.WriteLine("Measurement stopped. _isMeasuring is now " + _isMeasuring);
    }

    public bool IsMeasuring()
    {
        Console.WriteLine("IsMeasuring called. _isMeasuring is " + _isMeasuring);
        return _isMeasuring;
    }
}
