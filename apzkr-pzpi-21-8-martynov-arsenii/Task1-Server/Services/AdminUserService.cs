using System.Threading.Tasks;
using System.Collections.Generic;
using MongoDB.Driver;

public interface IAdminUserService
{
    Task<List<AdminUser>> GetAllUsersAsync();
    Task<AdminUser> GetUserByIdAsync(string id);
    Task<AdminUser> GetByUsernameAsync(string username);
    Task CreateUserAsync(AdminUser adminUser);
    Task UpdateUserAsync(string id, AdminUserUpdateModel adminUserUpdateModel);
    Task DeleteUserAsync(string id);
}


public class AdminUserService : IAdminUserService
{
    private readonly IAdminUserRepository _repository;

    public AdminUserService(IAdminUserRepository repository)
    {
        _repository = repository;
    }

    public async Task<List<AdminUser>> GetAllUsersAsync()
    {
        return await _repository.GetAllAsync();
    }

    public async Task<AdminUser> GetUserByIdAsync(string id)
    {
        return await _repository.GetByIdAsync(id);
    }

    public async Task<AdminUser> GetByUsernameAsync(string username)
    {
        return await _repository.GetByUsernameAsync(username);
    }

    public async Task CreateUserAsync(AdminUser adminUser)
    {
        await _repository.CreateAsync(adminUser);
    }

    public async Task UpdateUserAsync(string id, AdminUserUpdateModel adminUserUpdateModel)
    {
        var update = Builders<AdminUser>.Update
            .Set(u => u.Username, adminUserUpdateModel.Username)
            .Set(u => u.FirstName, adminUserUpdateModel.FirstName)
            .Set(u => u.LastName, adminUserUpdateModel.LastName)
            .Set(u => u.Email, adminUserUpdateModel.Email)
            .Set(u => u.Phone, adminUserUpdateModel.Phone)
            .Set(u => u.Role, adminUserUpdateModel.Role)
            .Set(u => u.Status, adminUserUpdateModel.Status);

        await _repository.UpdateAsync(id, update);
    }

    public async Task DeleteUserAsync(string id)
    {
        await _repository.DeleteAsync(id);
    }
}
