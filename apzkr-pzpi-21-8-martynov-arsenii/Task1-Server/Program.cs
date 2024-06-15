using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using MongoDB.Bson;
using MongoDB.Driver;
using System.IO;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.IdentityModel.Tokens;
using System.Text;


var builder = WebApplication.CreateBuilder(args);

// Êîíôèãóðàöèÿ äëÿ äîñòóïà ê appsettings.json
var configuration = new ConfigurationBuilder()
    .SetBasePath(Directory.GetCurrentDirectory())
    .AddJsonFile("appsettings.json")
    .Build();

// Ïîäêëþ÷åíèå ê MongoDB
builder.Services.AddSingleton<IMongoClient>(provider =>
{
    var connectionString = configuration.GetConnectionString("MongoDB");
    return new MongoClient(connectionString);
});

// Ïîäêëþ÷åíèå ê áàçå äàííûõ MongoDB
builder.Services.AddScoped(provider =>
{
    var client = provider.GetRequiredService<IMongoClient>();
    var databaseName = configuration.GetValue<string>("DatabaseSettings:DatabaseName");
    return client.GetDatabase(databaseName);
});

builder.Services.AddScoped<IAdminUserRepository, AdminUserRepository>();
builder.Services.AddScoped<IGardenRepository, GardenRepository>();
builder.Services.AddScoped<IEquipmentRepository, EquipmentRepository>();
builder.Services.AddScoped<IMeasurementRepository, MeasurementRepository>();
builder.Services.AddScoped<IRoomRepository, RoomRepository>();
builder.Services.AddScoped<IUserRepository, UserRepository>();


// Ðåãèñòðàöèÿ ñåðâèñîâ
builder.Services.AddScoped<IAdminUserService, AdminUserService>();
builder.Services.AddScoped<IGardenService, GardenService>();
builder.Services.AddScoped<IEquipmentService, EquipmentService>();
builder.Services.AddScoped<IMeasurementService, MeasurementService>();
builder.Services.AddScoped<IRoomService, RoomService>();
builder.Services.AddScoped<IUserService, UserService>();
builder.Services.AddScoped<ITokenService, TokenService>();

builder.Services.AddControllers();

// Íàñòðîéêà àóòåíòèôèêàöèè è àâòîðèçàöèè
builder.Services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
    .AddJwtBearer(options =>
    {
        options.TokenValidationParameters = new TokenValidationParameters
        {
            ValidateIssuer = true,
            ValidateAudience = true,
            ValidateLifetime = true,
            ValidateIssuerSigningKey = true,
            ValidIssuer = configuration["Jwt:Issuer"],
            ValidAudience = configuration["Jwt:Audience"],
            IssuerSigningKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(configuration["Jwt:Key"]))
        };
    });

builder.Services.AddAuthorization(options =>
{
    options.AddPolicy("AdminOnly", policy => policy.RequireRole("admin"));
    options.AddPolicy("EmployeeOnly", policy => policy.RequireRole("employee"));
});

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowReactApp",
        policy =>
        {
            policy.WithOrigins("http://localhost:3000") // àäðåñ âàøåãî React ïðèëîæåíèÿ
                  .AllowAnyHeader()
                  .AllowAnyMethod();
        });
});


var app = builder.Build();


app.UseCors("AllowReactApp");

app.UseAuthentication();
app.UseAuthorization();

// Äîáàâëåíèå ìàðøðóòà äëÿ êîðíåâîãî ïóòè
app.MapGet("/", () => "Hello World!");

// Äîáàâëåíèå ìàðøðóòà äëÿ êîíòðîëëåðà
app.MapControllers();

app.Run();

