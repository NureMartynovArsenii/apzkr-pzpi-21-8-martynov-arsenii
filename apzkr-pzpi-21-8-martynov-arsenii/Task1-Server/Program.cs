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

//var builder = WebApplication.CreateBuilder(args);

//// Конфигурация для доступа к appsettings.json
//var configuration = new ConfigurationBuilder()
//    .SetBasePath(Directory.GetCurrentDirectory())
//    .AddJsonFile("appsettings.json")
//    .Build();

//// Подключение к MongoDB
//builder.Services.AddSingleton<IMongoClient>(provider =>
//{
//    var connectionString = configuration.GetConnectionString("MongoDB");
//    return new MongoClient(connectionString);
//});

//// Подключение к базе данных MongoDB
//builder.Services.AddScoped(provider =>
//{
//    var client = provider.GetRequiredService<IMongoClient>();
//    var databaseName = configuration.GetValue<string>("DatabaseSettings:DatabaseName");
//    return client.GetDatabase(databaseName);
//});

//builder.Services.AddScoped<IAdminUserRepository, AdminUserRepository>();
//builder.Services.AddScoped<IGardenRepository, GardenRepository>();
//builder.Services.AddScoped<IEquipmentRepository, EquipmentRepository>();
//builder.Services.AddScoped<IMeasurementRepository, MeasurementRepository>();
//builder.Services.AddScoped<IRoomRepository, RoomRepository>();
//builder.Services.AddScoped<IUserRepository, UserRepository>();

//// Регистрация сервисов
//builder.Services.AddScoped<AdminUserService, AdminUserService>();
//builder.Services.AddScoped<IGardenService, GardenService>();
//builder.Services.AddScoped<IEquipmentService, EquipmentService>();
//builder.Services.AddScoped<IMeasurementService, MeasurementService>();
//builder.Services.AddScoped<IRoomService, RoomService>();
//builder.Services.AddScoped<IUserService, UserService>();
////// Добавление контроллера
//builder.Services.AddControllers();


//var app = builder.Build();

//// Добавление маршрута для корневого пути
//app.MapGet("/", () => "Hello World!");

//// Добавление маршрута для контроллера
//app.MapControllers();

//app.Run();

var builder = WebApplication.CreateBuilder(args);

// Конфигурация для доступа к appsettings.json
var configuration = new ConfigurationBuilder()
    .SetBasePath(Directory.GetCurrentDirectory())
    .AddJsonFile("appsettings.json")
    .Build();

// Подключение к MongoDB
builder.Services.AddSingleton<IMongoClient>(provider =>
{
    var connectionString = configuration.GetConnectionString("MongoDB");
    return new MongoClient(connectionString);
});

// Подключение к базе данных MongoDB
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


// Регистрация сервисов
builder.Services.AddScoped<IAdminUserService, AdminUserService>();
builder.Services.AddScoped<IGardenService, GardenService>();
builder.Services.AddScoped<IEquipmentService, EquipmentService>();
builder.Services.AddScoped<IMeasurementService, MeasurementService>();
builder.Services.AddScoped<IRoomService, RoomService>();
builder.Services.AddScoped<IUserService, UserService>();
builder.Services.AddScoped<ITokenService, TokenService>();

builder.Services.AddControllers();

// Настройка аутентификации и авторизации
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
            policy.WithOrigins("http://localhost:3000") // адрес вашего React приложения
                  .AllowAnyHeader()
                  .AllowAnyMethod();
        });
});


var app = builder.Build();


app.UseCors("AllowReactApp");

app.UseAuthentication();
app.UseAuthorization();

// Добавление маршрута для корневого пути
app.MapGet("/", () => "Hello World!");

// Добавление маршрута для контроллера
app.MapControllers();

app.Run();

