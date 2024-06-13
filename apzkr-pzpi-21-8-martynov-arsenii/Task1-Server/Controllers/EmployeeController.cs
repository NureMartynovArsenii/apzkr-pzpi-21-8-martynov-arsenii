using Amazon.Auth.AccessControlPolicy;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;


[Route("api/employee")]
[ApiController]
public class EmployeeController : ControllerBase
{
    private readonly ITokenService _tokenService;
    private readonly IAdminUserService _adminUserService;

    public EmployeeController(ITokenService tokenService, IAdminUserService adminUserService)
    {
        _tokenService = tokenService;
        _adminUserService = adminUserService;
    }

    [HttpPost("login")]
    public async Task<IActionResult> Login([FromBody] LoginModel loginModel)
    {
        var employeeUser = await _adminUserService.GetByUsernameAsync(loginModel.Username);

        if (employeeUser == null || employeeUser.Password != loginModel.Password) // Здесь должна быть проверка хеша пароля
        {
            return Unauthorized("Invalid username or password.");
        }

        var token = _tokenService.GenerateToken(employeeUser);
        return Ok(new { token, role = employeeUser.Role });
    }
}
