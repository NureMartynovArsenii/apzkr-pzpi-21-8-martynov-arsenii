//import { useState, useEffect } from 'react';
//import { useTranslation } from 'react-i18next';
//import { useNavigate } from 'react-router-dom';

//const UserSettings = () => {
//    const { t } = useTranslation();
//    const [userData, setUserData] = useState({ username: '', firstName: '', lastName: '', email: '', phone: '' });
//    const [message, setMessage] = useState('');
//    const navigate = useNavigate();

//    useEffect(() => {
//        fetchUserData();
//    }, []);

//    const fetchUserData = async () => {
//        try {
//            const token = localStorage.getItem('token');
//            const response = await fetch('https://localhost:7077/api/users/me', {
//                headers: {
//                    'Authorization': `Bearer ${token}`
//                }
//            });
//            const data = await response.json();
//            if (response.ok) {
//                setUserData(data);
//            } else {
//                setMessage(data.Message || 'Error fetching user data');
//            }
//        } catch (error) {
//            console.error('Ошибка при получении данных пользователя:', error);
//        }
//    };

//    const handleChange = (e) => {
//        const { name, value } = e.target;
//        setUserData({ ...userData, [name]: value });
//    };

//    const handleSubmit = async (e) => {
//        e.preventDefault();
//        try {
//            const token = localStorage.getItem('token');
//            const response = await fetch('https://localhost:7077/api/users/me', {
//                method: 'PUT',
//                headers: {
//                    'Content-Type': 'application/json',
//                    'Authorization': `Bearer ${token}`
//                },
//                body: JSON.stringify(userData)
//            });
//            const data = await response.json();
//            if (response.ok) {
//                setMessage('User updated successfully');
//                navigate('/gardens');
//            } else {
//                setMessage(data.Message || 'Error updating user data');
//            }
//        } catch (error) {
//            console.error('Ошибка при обновлении данных пользователя:', error);
//        }
//    };

//    return (
//        <div className="user-settings-container">
//            <h1>{t('User Settings')}</h1>
//            <form className="user-settings-form" onSubmit={handleSubmit}>
//                <input
//                    type="text"
//                    name="username"
//                    placeholder={t('Username')}
//                    value={userData.username}
//                    onChange={handleChange}
//                />
//                <input
//                    type="text"
//                    name="firstName"
//                    placeholder={t('First Name')}
//                    value={userData.firstName}
//                    onChange={handleChange}
//                />
//                <input
//                    type="text"
//                    name="lastName"
//                    placeholder={t('Last Name')}
//                    value={userData.lastName}
//                    onChange={handleChange}
//                />
//                <input
//                    type="email"
//                    name="email"
//                    placeholder={t('Email')}
//                    value={userData.email}
//                    onChange={handleChange}
//                />
//                <input
//                    type="text"
//                    name="phone"
//                    placeholder={t('Phone')}
//                    value={userData.phone}
//                    onChange={handleChange}
//                />
//                <button type="submit">{t('Save')}</button>
//                {message && <p>{message}</p>}
//            </form>
//        </div>
//    );
//};

//export default UserSettings;
import { useState, useEffect } from 'react';
import { useTranslation } from 'react-i18next';
import { useNavigate } from 'react-router-dom';
import FullScreenImage from './components/FullScreenImage'; // Import the FullScreenImage component
import './UserSettings.css'; // Import the CSS file for styling

const UserSettings = () => {
    const { t } = useTranslation();
    const [userData, setUserData] = useState({ username: '', firstName: '', lastName: '', email: '', phone: '' });
    const [message, setMessage] = useState('');

    useEffect(() => {
        fetchUserData();
    }, []);

    const fetchUserData = async () => {
        try {
            const token = localStorage.getItem('token');
            const response = await fetch('https://localhost:7077/api/users/me', {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });
            const data = await response.json();
            if (response.ok) {
                setUserData(data);
            } else {
                setMessage(data.Message || 'Error fetching user data');
            }
        } catch (error) {
            console.error('Ошибка при получении данных пользователя:', error);
        }
    };

    const handleChange = (e) => {
        const { name, value } = e.target;
        setUserData({ ...userData, [name]: value });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const token = localStorage.getItem('token');
            const response = await fetch('https://localhost:7077/api/users/me', {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`
                },
                body: JSON.stringify(userData)
            });
            const data = await response.json();
            if (response.ok) {
                setMessage(t('User updated successfully'));
            } else {
                setMessage(data.Message || t('Error updating user data'));
            }
        } catch (error) {
            console.error('Ошибка при обновлении данных пользователя:', error);
        }
    };

    return (
        <div>
            <FullScreenImage />
            <div className="user-settings-container">
                <h1>{t('UserSettings')}</h1>
                <form className="user-settings-form" onSubmit={handleSubmit}>
                    <div className="form-group">
                        <label>{t('Username')}</label>
                        <input
                            type="text"
                            name="username"
                            placeholder={t('Username')}
                            value={userData.username}
                            onChange={handleChange}
                        />
                    </div>
                    <div className="form-group">
                        <label>{t('FirstName')}</label>
                        <input
                            type="text"
                            name="firstName"
                            placeholder={t('FirstName')}
                            value={userData.firstName}
                            onChange={handleChange}
                        />
                    </div>
                    <div className="form-group">
                        <label>{t('LastName')}</label>
                        <input
                            type="text"
                            name="lastName"
                            placeholder={t('LastName')}
                            value={userData.lastName}
                            onChange={handleChange}
                        />
                    </div>
                    <div className="form-group">
                        <label>{t('Email')}</label>
                        <input
                            type="email"
                            name="email"
                            placeholder={t('Email')}
                            value={userData.email}
                            onChange={handleChange}
                        />
                    </div>
                    <div className="form-group">
                        <label>{t('Phone')}</label>
                        <input
                            type="text"
                            name="phone"
                            placeholder={t('Phone')}
                            value={userData.phone}
                            onChange={handleChange}
                        />
                    </div>
                    <button type="submit" className="save-button">{t('Save')}</button>
                    {message && <p className="message">{message}</p>}
                </form>
            </div>
        </div>
    );
};

export default UserSettings;