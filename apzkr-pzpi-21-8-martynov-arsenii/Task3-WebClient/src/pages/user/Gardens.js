import React, { useEffect, useState } from 'react';
import FullScreenImage from './components/FullScreenImage';
import './Gardens.css';
import { useNavigate } from 'react-router-dom';
import './Gardens.css';
import { useTranslation } from 'react-i18next';

const Gardens = () => {
    const { t } = useTranslation();
    const [garden, setGarden] = useState(null);
    const [formData, setFormData] = useState({
        name: '',
        location: '',
        director: '',
        email: '',
        phone: ''
    });
    const [message, setMessage] = useState('');
    const navigate = useNavigate();

    useEffect(() => {
        fetchUserGarden();
    }, []);

    const fetchUserGarden = async () => {
        try {
            const token = localStorage.getItem('token');
            const response = await fetch('https://localhost:7077/api/gardens/user-garden', {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            });
            if (!response.ok) {
                const errorData = await response.json();
                console.error('Error fetching garden:', errorData.message);
                setGarden(null);
                return;
            }
            const data = await response.json();
            setGarden(data);
            setFormData({
                name: data.name,
                location: data.location,
                director: data.director,
                email: data.email,
                phone: data.phone
            });
        } catch (error) {
            console.error('Error fetching garden:', error);
        }
    };

    const handleViewRooms = (gardenId) => {
        navigate(`/gardens/${gardenId}/rooms`);
    };

    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData({ ...formData, [name]: value });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const token = localStorage.getItem('token');
            const response = await fetch('https://localhost:7077/api/gardens/user-garden', {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`
                },
                body: JSON.stringify(formData)
            });
            if (!response.ok) {
                const errorData = await response.json();
                setMessage(errorData.message || t('Error updating garden'));
                return;
            }
            setMessage(t('Garden updated successfully'));
            fetchUserGarden();
        } catch (error) {
            console.error('Error updating garden:', error);
            setMessage(t('Error updating garden'));
        }
    };

    return (
        <div className="gardens-container">
            <FullScreenImage />
            <div className="gardens-content">
                <h1>{t('WelcomeToGarden')}</h1>
                {garden ? (
                    <div className="vertical-menu">
                        <div className="menu-item">
                            <strong>{t('Name')}:</strong> {garden.name}
                        </div>
                        <div className="menu-item">
                            <strong>{t('Location')}:</strong> {garden.location}
                        </div>
                        <div className="menu-item">
                            <strong>{t('Director')}:</strong> {garden.director}
                        </div>
                        <div className="menu-item">
                            <strong>{t('Email')}:</strong> {garden.email}
                        </div>
                        <div className="menu-item">
                            <strong>{t('Phone')}:</strong> {garden.phone}
                        </div>
                        <div className="menu-item">
                            <button onClick={() => handleViewRooms(garden.id)}>{t('Rooms')}</button>
                        </div>
                        <form onSubmit={handleSubmit}>
                            <div className="form-group">
                                <label>{t('Name')}</label>
                                <input
                                    type="text"
                                    name="name"
                                    value={formData.name}
                                    onChange={handleChange}
                                />
                            </div>
                            <div className="form-group">
                                <label>{t('Location')}</label>
                                <input
                                    type="text"
                                    name="location"
                                    value={formData.location}
                                    onChange={handleChange}
                                />
                            </div>
                            <div className="form-group">
                                <label>{t('Director')}</label>
                                <input
                                    type="text"
                                    name="director"
                                    value={formData.director}
                                    onChange={handleChange}
                                />
                            </div>
                            <div className="form-group">
                                <label>{t('Email')}</label>
                                <input
                                    type="email"
                                    name="email"
                                    value={formData.email}
                                    onChange={handleChange}
                                />
                            </div>
                            <div className="form-group">
                                <label>{t('Phone')}</label>
                                <input
                                    type="text"
                                    name="phone"
                                    value={formData.phone}
                                    onChange={handleChange}
                                />
                            </div>
                            <button type="submit" className="save-button">{t('Save')}</button>
                            {message && <p className="message">{message}</p>}
                        </form>
                    </div>
                ) : (
                    <p>{t('NoGardenAssigned')}</p>
                )}
            </div>
        </div>
    );
};

export default Gardens;
