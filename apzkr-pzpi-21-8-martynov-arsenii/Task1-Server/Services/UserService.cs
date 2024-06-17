using MongoDB.Driver;

public interface IUserService
{
    Task<List<Users>> GetAllAsync();
    Task<Users> GetByIdAsync(string id);
    Task<Users> GetByUsernameAsync(string username);
    Task<Users> GetByEmailAsync(string email);
    Task<Users> CreateAsync(CreateUsersModel createUserModel);
    Task UpdateAsync(string id, CreateUsersModel updateUserModel);
    Task DeleteAsync(string id);

}

public class UserService : IUserService
{
    private readonly IUserRepository _userRepository;

    public UserService(IUserRepository userRepository)
    {
        _userRepository = userRepository;
    }

    public async Task<List<Users>> GetAllAsync()
    {
        return await _userRepository.GetAllAsync();
    }

    public async Task<Users> GetByIdAsync(string id)
    {
        return await _userRepository.GetByIdAsync(id);
    }

    public async Task<Users> GetByUsernameAsync(string username)
    {
        return await _userRepository.GetByUsernameAsync(username);
    }
    public async Task<Users> GetByEmailAsync(string email) // Implement this method
    {
        return await _userRepository.GetByEmailAsync(email);
    }
    public async Task<Users> CreateAsync(CreateUsersModel createUserModel)
    {
        var existingUser = await _userRepository.GetByUsernameAsync(createUserModel.Username);
        if (existingUser != null)
        {
            throw new Exception("Username already exists");
        }
        var existingEmail = await _userRepository.GetByEmailAsync(createUserModel.Email);
        if (existingEmail != null)
        {
            throw new Exception("Email already exists");
        }
        var user = new Users
        {
            Username = createUserModel.Username,
            FirstName = createUserModel.FirstName,
            LastName = createUserModel.LastName,
            Email = createUserModel.Email,
            Password = createUserModel.Password,
            Phone = createUserModel.Phone,
            Role = createUserModel.Role,
            Status = "Active"
        };
        await _userRepository.CreateAsync(user);
        return user;
    }

    public async Task UpdateAsync(string id, CreateUsersModel updateUserModel)
    {
        var update = Builders<Users>.Update
            .Set(u => u.Username, updateUserModel.Username)
            .Set(u => u.FirstName, updateUserModel.FirstName)
            .Set(u => u.LastName, updateUserModel.LastName)
            .Set(u => u.Email, updateUserModel.Email)
            .Set(u => u.Password, updateUserModel.Password)
            .Set(u => u.Phone, updateUserModel.Phone)
            .Set(u => u.Role, updateUserModel.Role);
        await _userRepository.UpdateAsync(id, update);
    }

    public async Task DeleteAsync(string id)
    {
        await _userRepository.DeleteAsync(id);
    }
}
