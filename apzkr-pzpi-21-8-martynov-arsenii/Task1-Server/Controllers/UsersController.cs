using MongoDB.Driver;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson.Serialization.Attributes;
using MongoDB.Bson;
using Microsoft.AspNetCore.Authorization;


//[Route("api/[controller]")]
//[ApiController]
//public class UsersController : ControllerBase
//{
//    private readonly IMongoCollection<Users> _usersCollection;

//    public UsersController(IMongoClient client)
//    {
//        var database = client.GetDatabase("ChildClimaCare");
//        _usersCollection = database.GetCollection<Users>("User");
//    }



//    [HttpGet("{id:length(24)}", Name = "GetUserById")]
//    public async Task<ActionResult<Users>> GetUserById(string id)
//    {
//        var user = await _usersCollection.Find(u => u.Id == id).FirstOrDefaultAsync();
//        if (user == null)
//        {
//            return NotFound("Користувача з таким ID не знайдено.");
//        }
//        return user;
//    }

//    [HttpPost("register")]
//    public async Task<IActionResult> Register([FromBody] CreateUsersModel createUserModel)
//    {
//        // Перевірка, чи існує користувач з таким Email або Username
//        var existingUser = await _usersCollection.Find(u => u.Email == createUserModel.Email || u.Username == createUserModel.Username).FirstOrDefaultAsync();
//        if (existingUser != null)
//        {
//            return BadRequest("Користувач з таким Email або Username вже існує.");
//        }

//        var user = new Users
//        {
//            Username = createUserModel.Username,
//            FirstName = createUserModel.FirstName,
//            LastName = createUserModel.LastName,
//            Email = createUserModel.Email,
//            Password = createUserModel.Password, // Тут має бути хешування паролю перед збереженням
//            Phone = createUserModel.Phone,
//            Role = createUserModel.Role,
//            Status = createUserModel.Status
//        };

//        await _usersCollection.InsertOneAsync(user);
//        return CreatedAtRoute("GetUserById", new { id = user.Id }, user);
//    }

//    [HttpPost("login")]
//    public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
//    {
//        var user = await _usersCollection.Find(u => u.Username == loginModel.Username).FirstOrDefaultAsync();

//        if (user == null || user.Password != loginModel.Password)
//        {
//            return Unauthorized("Неправильне ім'я користувача або пароль.");
//        }

//        if (user.Status == "Banned")
//        {
//            return Unauthorized("Ваш обліковий запис заблоковано.");
//        }


//        return Ok("Вхід в систему успішний.");
//    }



//    // Додайте тут інші методи API...
//}
//[Route("api/[controller]")]
//[ApiController]
//public class UsersController : ControllerBase
//{
//    private readonly IUserService _userService;

//    public UsersController(IUserService userService)
//    {
//        _userService = userService;
//    }

//    [HttpGet]
//    public async Task<ActionResult<List<Users>>> GetAllUsers()
//    {
//        var users = await _userService.GetAllAsync();
//        return Ok(users);
//    }

//    [HttpGet("{id:length(24)}", Name = "GetUserById")]
//    public async Task<ActionResult<Users>> GetUserById(string id)
//    {
//        var user = await _userService.GetByIdAsync(id);
//        if (user == null)
//        {
//            return NotFound("User with this ID not found.");
//        }
//        return Ok(user);
//    }

//    [HttpGet("username/{username}", Name = "GetUserByUsername")]
//    public async Task<ActionResult<Users>> GetUserByUsername(string username)
//    {
//        var user = await _userService.GetByUsernameAsync(username);
//        if (user == null)
//        {
//            return NotFound("User with this username not found.");
//        }
//        return Ok(user);
//    }

//    [HttpPost("register")]
//    public async Task<IActionResult> Register([FromBody] CreateUsersModel createUserModel)
//    {
//        var createdUser = await _userService.CreateAsync(createUserModel);
//        return CreatedAtAction(nameof(GetUserById), new { id = createdUser.Id }, createdUser);
//    }

//    [HttpPut("{id:length(24)}")]
//    public async Task<IActionResult> UpdateUser(string id, [FromBody] CreateUsersModel updateUserModel)
//    {
//        await _userService.UpdateAsync(id, updateUserModel);
//        return Ok("User updated successfully.");
//    }

//    [HttpDelete("{id:length(24)}")]
//    public async Task<IActionResult> DeleteUser(string id)
//    {
//        await _userService.DeleteAsync(id);
//        return Ok("User deleted successfully.");
//    }

//    [HttpPost("login")]
//    public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
//    {
//        var user = await _userService.GetByUsernameAsync(loginModel.Username);

//        if (user == null || user.Password != loginModel.Password) // Здесь должна быть проверка хеша пароля
//        {
//            return Unauthorized("Invalid username or password.");
//        }

//        if (user.Status == "Banned")
//        {
//            return Unauthorized("Your account has been banned.");
//        }

//        return Ok(new { message = "Login successful" });
//    }
//}

//[Route("api/[controller]")]
//[ApiController]
//public class UsersController : ControllerBase
//{
//    private readonly IUserService _userService;

//    public UsersController(IUserService userService)
//    {
//        _userService = userService;

//    }
//    //[HttpGet("me")]
//    //public async Task<IActionResult> GetCurrentUser()
//    //{
//    //    var username = User.Identity.Name;
//    //    var user = await _userService.GetByUsernameAsync(username);
//    //    if (user == null)
//    //    {
//    //        return NotFound(new { Message = "User not found" });
//    //    }
//    //    return Ok(user);
//    //}

//    //[HttpPut("me")]
//    //public async Task<IActionResult> UpdateCurrentUser([FromBody] CreateUsersModel updateUserModel)
//    //{
//    //    var username = User.Identity.Name;
//    //    var user = await _userService.GetByUsernameAsync(username);
//    //    if (user == null)
//    //    {
//    //        return NotFound(new { Message = "User not found" });
//    //    }
//    //    await _userService.UpdateAsync(user.Id, updateUserModel);
//    //    return Ok(new { Message = "User updated successfully" });
//    //}
//    [HttpGet]
//    public async Task<ActionResult<List<Users>>> GetAllUsers()
//    {
//        var users = await _userService.GetAllAsync();
//        return Ok(users);
//    }

//    [HttpGet("{id:length(24)}", Name = "GetUserById")]
//    public async Task<ActionResult<Users>> GetUserById(string id)
//    {
//        var user = await _userService.GetByIdAsync(id);
//        if (user == null)
//        {
//            return NotFound("User with this ID not found.");
//        }
//        return Ok(user);
//    }

//    [HttpGet("username/{username}", Name = "GetUserByUsername")]
//    public async Task<ActionResult<Users>> GetUserByUsername(string username)
//    {
//        var user = await _userService.GetByUsernameAsync(username);
//        if (user == null)
//        {
//            return NotFound("User with this username not found.");
//        }
//        return Ok(user);
//    }

//    [HttpPost("register")]
//    public async Task<IActionResult> Register([FromBody] CreateUsersModel createUserModel)
//    {
//        var createdUser = await _userService.CreateAsync(createUserModel);
//        return CreatedAtAction(nameof(GetUserById), new { id = createdUser.Id }, createdUser);
//    }

//    [HttpPut("{id:length(24)}")]
//    public async Task<IActionResult> UpdateUser(string id, [FromBody] CreateUsersModel updateUserModel)
//    {
//        await _userService.UpdateAsync(id, updateUserModel);
//        return Ok("User updated successfully.");
//    }

//    [HttpDelete("{id:length(24)}")]
//    public async Task<IActionResult> DeleteUser(string id)
//    {
//        await _userService.DeleteAsync(id);
//        return Ok("User deleted successfully.");
//    }

//    [HttpPost("login")]
//    public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
//    {
//        var user = await _userService.GetByUsernameAsync(loginModel.Username);

//        if (user == null || user.Password != loginModel.Password) // Здесь должна быть проверка хеша пароля
//        {
//            return Unauthorized("Invalid username or password.");
//        }

//        if (user.Status == "Banned")
//        {
//            return Unauthorized("Your account has been banned.");
//        }

//        return Ok(new { message = "Login successful" });
//    }



//}


[Route("api/[controller]")]
[ApiController]
public class UsersController : ControllerBase
{
    private readonly IUserService _userService;
    private readonly ITokenService _tokenService;
    private readonly IGardenService _gardenService;
    public UsersController(IUserService userService, ITokenService tokenService, IGardenService gardenService)
    {
        _userService = userService;
        _tokenService = tokenService;
        _gardenService = gardenService;
    }

    [HttpGet("me")]
    public async Task<IActionResult> GetCurrentUser()
    {
        var username = User.Identity.Name;
        var user = await _userService.GetByUsernameAsync(username);
        if (user == null)
        {
            return NotFound(new { Message = "User not found" });
        }
        return Ok(user);
    }

    [HttpPut("me")]
    public async Task<IActionResult> UpdateCurrentUser([FromBody] CreateUsersModel updateUserModel)
    {
        var username = User.Identity.Name;
        var user = await _userService.GetByUsernameAsync(username);
        if (user == null)
        {
            return NotFound(new { Message = "User not found" });
        }
        await _userService.UpdateAsync(user.Id, updateUserModel);
        return Ok(new { Message = "User updated successfully" });
    }

    [HttpGet]
    public async Task<ActionResult<List<Users>>> GetAllUsers()
    {
        var users = await _userService.GetAllAsync();
        return Ok(users);
    }

    [HttpGet("{id:length(24)}", Name = "GetUserById")]
    public async Task<ActionResult<Users>> GetUserById(string id)
    {
        var user = await _userService.GetByIdAsync(id);
        if (user == null)
        {
            return NotFound("User with this ID not found.");
        }
        return Ok(user);
    }

    [HttpGet("username/{username}", Name = "GetUserByUsername")]
    public async Task<ActionResult<Users>> GetUserByUsername(string username)
    {
        var user = await _userService.GetByUsernameAsync(username);
        if (user == null)
        {
            return NotFound("User with this username not found.");
        }
        return Ok(user);
    }

    [HttpPost("register")]
    public async Task<IActionResult> Register([FromBody] CreateUsersModel createUserModel)
    {
        //var createdUser = await _userService.CreateAsync(createUserModel);
        //return CreatedAtAction(nameof(GetUserById), new { id = createdUser.Id }, createdUser);
        try
        {
            var createdUser = await _userService.CreateAsync(createUserModel);
            return CreatedAtAction(nameof(GetUserById), new { id = createdUser.Id }, createdUser);
        }
        catch (Exception ex)
        {
            return BadRequest(new { message = ex.Message });
        }
    }

    [HttpPut("{id:length(24)}")]
    public async Task<IActionResult> UpdateUser(string id, [FromBody] CreateUsersModel updateUserModel)
    {
        await _userService.UpdateAsync(id, updateUserModel);
        return Ok("User updated successfully.");
    }

    [HttpDelete("{id:length(24)}")]
    public async Task<IActionResult> DeleteUser(string id)
    {
        await _userService.DeleteAsync(id);
        return Ok("User deleted successfully.");
    }

    //[HttpPost("login")]
    //public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
    //{
    //    var user = await _userService.GetByUsernameAsync(loginModel.Username);

    //    if (user == null || user.Password != loginModel.Password) // Здесь должна быть проверка хеша пароля
    //    {
    //        return Unauthorized("Invalid username or password.");
    //    }

    //    if (user.Status == "Banned")
    //    {
    //        return Unauthorized("Your account has been banned.");
    //    }

    //    var token = _tokenService.GenerateToken(user);
    //    return Ok(new { token, role = user.Role });
    //}
    //[HttpPost("login")]
    //public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
    //{
    //    var user = await _userService.GetByUsernameAsync(loginModel.Username);

    //    if (user == null || user.Password != loginModel.Password) // Здесь должна быть проверка хеша пароля
    //    {
    //        return Unauthorized(new { message = "Invalid username or password." });
    //    }

    //    if (user.Status == "Banned")
    //    {
    //        return Unauthorized(new { message = "Your account has been banned." });
    //    }

    //    var token = _tokenService.GenerateToken(user);
    //    return Ok(new { token, role = user.Role });
    //}
    [HttpPost("login")]
    public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
    {
        var user = await _userService.GetByUsernameAsync(loginModel.Username);

        if (user == null || user.Password != loginModel.Password) // Тут має бути перевірка хеша пароля
        {
            return Unauthorized(new { message = "Invalid username or password." });
        }

        if (user.Status == "Banned")
        {
            return Unauthorized(new { message = "Your account has been banned." });
        }

        var token = _tokenService.GenerateToken(user);
        var userGarden = await _gardenService.GetGardenByUserIdAsync(user.Id);

        return Ok(new { token, role = user.Role, gardenId = userGarden?.Id });
    }

    [HttpPost("logout")]
    public IActionResult Logout()
    {
        // Додайте тут код, якщо потрібно управляти сесіями на стороні сервера
        return Ok(new { Message = "Logged out successfully" });
    }
}

[BsonIgnoreExtraElements]
public class Users
{
    [BsonId]
    [BsonRepresentation(BsonType.ObjectId)]
    public string Id { get; set; }
    public string Username { get; set; }
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public string Email { get; set; }
    // Пароль не повинен бути відображений у відповіді API
    public string Password { get; set; }
    public string Phone { get; set; }
    public string Role { get; set; }
    public string Status { get; set; }
}


public class LoginModel
{
    public string Username { get; set; }
    public string Password { get; set; }
}

public class CreateUsersModel
{
    public string Username { get; set; }
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public string Email { get; set; }
    public string Password { get; set; }
    public string Phone { get; set; }
    public string Role { get; set; }
}
