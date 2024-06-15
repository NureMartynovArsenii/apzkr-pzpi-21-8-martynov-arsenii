import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import FullScreenImage from './components/FullScreenImage';
import './Rooms.css';
import { useNavigate } from 'react-router-dom';
import { useTranslation } from 'react-i18next';


const Rooms = () => {
    const { t } = useTranslation();
    const { gardenId } = useParams();
    const [rooms, setRooms] = useState([]);
    const [formData, setFormData] = useState({ roomNumber: '', capacity: '' });
    const [searchTerm, setSearchTerm] = useState('');
    const [capacityFilter, setCapacityFilter] = useState('');
    const [message, setMessage] = useState('');
    const navigate = useNavigate();

    useEffect(() => {
        fetchRooms();
    }, []);

    const fetchRooms = async () => {
        try {
            const response = await fetch(`https://localhost:7077/api/gardens/${gardenId}/rooms`);
            const data = await response.json();
            setRooms(data);
        } catch (error) {
            console.error('Ошибка при получении комнат:', error);
        }
    };

    const handleViewEquipment = (roomId) => {
        navigate(`/rooms/${roomId}/equipment`);
    };

    const handleSearch = (e) => {
        setSearchTerm(e.target.value);
    };

    const handleCapacityFilter = (e) => {
        setCapacityFilter(e.target.value);
    };

    const filteredRooms = rooms.filter(room =>
        room.roomNumber.toLowerCase().includes(searchTerm.toLowerCase()) &&
        (!capacityFilter || room.capacity.toString() === capacityFilter)
    );

    const handleChange = (e) => {
        const { name, value } = e.target;
        setFormData({ ...formData, [name]: value });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await fetch(`https://localhost:7077/api/rooms`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ ...formData, gardenId })
            });
            if (response.ok) {
                setMessage(t('Room created successfully'));
                fetchRooms();
            } else {
                setMessage(t('Error creating room'));
            }
        } catch (error) {
            console.error('Ошибка при создании комнаты:', error);
            setMessage(t('Error creating room'));
        }
    };

    const handleDeleteRoom = async (roomId) => {
        try {
            const response = await fetch(`https://localhost:7077/api/rooms/${roomId}`, {
                method: 'DELETE'
            });
            if (response.ok) {
                setMessage(t('Room deleted successfully'));
                fetchRooms();
            } else {
                setMessage(t('Error deleting room'));
            }
        } catch (error) {
            console.error('Ошибка при удалении комнаты:', error);
            setMessage(t('Error deleting room'));
        }
    };

    return (
        <div className="rooms-container">
            <FullScreenImage />
            <div className="rooms-content">
                <h1>{t('Rooms in Garden')}</h1>
                <input
                    type="text"
                    placeholder={t('Search by room number')}
                    value={searchTerm}
                    onChange={handleSearch}
                    className="search-input"
                />
                <input
                    type="text"
                    placeholder={t('Filter by capacity')}
                    value={capacityFilter}
                    onChange={handleCapacityFilter}
                    className="capacity-input"
                />
                <form onSubmit={handleSubmit} className="room-form">
                    <input
                        type="text"
                        name="roomNumber"
                        placeholder={t('Room Number')}
                        value={formData.roomNumber}
                        onChange={handleChange}
                        required
                    />
                    <input
                        type="number"
                        name="capacity"
                        placeholder={t('Quantity children')}
                        value={formData.capacity}
                        onChange={handleChange}
                        required
                    />
                    <button type="submit">{t('Create Room')}</button>
                </form>
                {message && <p className="message">{message}</p>}
                <table className="rooms-table">
                    <thead>
                        <tr>
                            <th>{t('Room Number')}</th>
                            <th>{t('Quantity children')}</th>
                            <th>{t('Actions')}</th>
                        </tr>
                    </thead>
                    <tbody>
                        {filteredRooms.map((room) => (
                            <tr key={room.id}>
                                <td>{room.roomNumber}</td>
                                <td>{room.capacity}</td>
                                <td>
                                    <button onClick={() => handleViewEquipment(room.id)}>{t('Equipment')}</button>
                                    <button onClick={() => handleDeleteRoom(room.id)}>{t('Delete')}</button>
                                </td>
                            </tr>
                        ))}
                    </tbody>
                </table>
            </div>
        </div>
    );
};

export default Rooms;
