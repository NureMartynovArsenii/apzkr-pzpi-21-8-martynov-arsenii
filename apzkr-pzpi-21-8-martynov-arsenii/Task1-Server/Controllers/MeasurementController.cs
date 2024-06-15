using MongoDB.Driver;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson.Serialization.Attributes;
using MongoDB.Bson;
using System.Diagnostics.Metrics;


[Route("api/[controller]")]
[ApiController]
public class MeasurementsController : ControllerBase
{
    private readonly IMeasurementService _measurementService;

    public MeasurementsController(IMeasurementService measurementService)
    {
        _measurementService = measurementService;
    }

    [HttpGet]
    public async Task<ActionResult<List<Measurement>>> GetAllMeasurements()
    {
        var measurements = await _measurementService.GetAllAsync();
        return Ok(measurements);
    }

    [HttpGet("{id:length(24)}", Name = "GetMeasurement")]
    public async Task<ActionResult<Measurement>> GetMeasurementById(string id)
    {
        var measurement = await _measurementService.GetByIdAsync(id);
        if (measurement == null)
        {
            return NotFound("Measurement with this ID not found.");
        }
        return Ok(measurement);
    }

    [HttpDelete("{id:length(24)}")]
    public async Task<IActionResult> DeleteMeasurement(string id)
    {
        await _measurementService.DeleteAsync(id);
        return Ok("Measurement deleted successfully.");
    }

    [HttpPost]
    public async Task<IActionResult> CreateMeasurement([FromBody] MeasurementCreateModel measurementCreateModel)
    {
        var createdMeasurement = await _measurementService.CreateAndGetAsync(measurementCreateModel);
        if (createdMeasurement == null)
        {
            return StatusCode(500, "An error occurred while creating the measurement.");
        }

        return CreatedAtRoute("GetMeasurement", new { id = createdMeasurement.Id }, createdMeasurement);
    }


    [HttpPut("{id:length(24)}")]
    public async Task<IActionResult> UpdateMeasurement(string id, [FromBody] MeasurementUpdateModel measurementUpdateModel)
    {
        await _measurementService.UpdateAsync(id, measurementUpdateModel);
        return Ok("Measurement updated successfully.");
    }
}

