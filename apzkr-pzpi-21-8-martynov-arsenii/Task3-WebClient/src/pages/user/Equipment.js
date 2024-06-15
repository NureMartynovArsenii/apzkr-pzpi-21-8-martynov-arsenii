import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import FullScreenImage from './components/FullScreenImage';
import './Equipment.css';
import { useNavigate } from 'react-router-dom';
import { useTranslation } from 'react-i18next';

const Equipment = () => {
    const { t } = useTranslation();
    const { roomId } = useParams();
    const [equipment, setEquipment] = useState([]);
    const [searchTerm, setSearchTerm] = useState('');
    const [statusFilter, setStatusFilter] = useState('');
    const [newEquipmentName, setNewEquipmentName] = useState('');
    const [newEquipmentStatus, setNewEquipmentStatus] = useState('');
    const [message, setMessage] = useState('');
    const navigate = useNavigate();

    useEffect(() => {
        fetchEquipment();
    }, []);

    const fetchEquipment = async () => {
        try {
            const response = await fetch(`https://localhost:7077/api/rooms/${roomId}/equipment`);
            const data = await response.json();
            setEquipment(data);
        } catch (error) {
            console.error('Ошибка при получении оборудования:', error);
        }
    };

    const handleViewMeasurements = (equipmentId) => {
        navigate(`/equipment/${equipmentId}/measurements`);
    };

    const handleSearch = (e) => {
        setSearchTerm(e.target.value);
    };

    const handleStatusFilter = (e) => {
        setStatusFilter(e.target.value);
    };

    const handleDeleteEquipment = async (equipmentId) => {
        try {
            const response = await fetch(`https://localhost:7077/api/equipment/${equipmentId}`, {
                method: 'DELETE',
            });
            if (response.ok) {
                setEquipment(equipment.filter(item => item.id !== equipmentId));
                setMessage(t('Equipment deleted successfully'));
            } else {
                console.error('Ошибка при удалении оборудования');
                setMessage(t('Error deleting equipment'));
            }
        } catch (error) {
            console.error('Ошибка при удалении оборудования:', error);
            setMessage(t('Error deleting equipment'));
        }
    };

    const handleCreateEquipment = async () => {
        try {
            const response = await fetch('https://localhost:7077/api/equipment', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    name: newEquipmentName,
                    status: newEquipmentStatus,
                    roomId: roomId,
                }),
            });
            const data = await response.json();
            if (response.ok) {
                setEquipment([...equipment, data]);
                setNewEquipmentName('');
                setNewEquipmentStatus('');
                setMessage(t('Equipment created successfully'));
            } else {
                console.error('Ошибка при создании оборудования');
                setMessage(t('Error creating equipment'));
            }
        } catch (error) {
            console.error('Ошибка при создании оборудования:', error);
            setMessage(t('Error creating equipment'));
        }
    };

    const handleStartMeasurement = async () => {
        try {
            const response = await fetch('https://localhost:7077/api/equipment/start', {
                method: 'POST',
            });
            if (response.ok) {
                setMessage(t('Measurement started'));
            } else {
                console.error('Ошибка при запуске измерений');
                setMessage(t('Error starting measurement'));
            }
        } catch (error) {
            console.error('Ошибка при запуске измерений:', error);
            setMessage(t('Error starting measurement'));
        }
    };

    const handleStopMeasurement = async () => {
        try {
            const response = await fetch('https://localhost:7077/api/equipment/stop', {
                method: 'POST',
            });
            if (response.ok) {
                setMessage(t('Measurement stopped'));
            } else {
                console.error('Ошибка при остановке измерений');
                setMessage(t('Error stopping measurement'));
            }
        } catch (error) {
            console.error('Ошибка при остановке измерений:', error);
            setMessage(t('Error stopping measurement'));
        }
    };

    const filteredEquipment = equipment.filter(item =>
        item.name.toLowerCase().includes(searchTerm.toLowerCase()) &&
        (!statusFilter || item.status.toLowerCase() === statusFilter.toLowerCase())
    );

    return (
        <div className="equipment-container">
            <FullScreenImage />
            <div className="equipment-content">
                <h1>{t('Equipment in Room')}</h1>
                <input
                    type="text"
                    placeholder={t('Search by name')}
                    value={searchTerm}
                    onChange={handleSearch}
                    className="search-input"
                />
                <input
                    type="text"
                    placeholder={t('Filter by status')}
                    value={statusFilter}
                    onChange={handleStatusFilter}
                    className="status-input"
                />
                <div className="create-equipment">
                    <input
                        type="text"
                        placeholder={t('Equipment Name')}
                        value={newEquipmentName}
                        onChange={(e) => setNewEquipmentName(e.target.value)}
                    />
                    <input
                        type="text"
                        placeholder={t('Status')}
                        value={newEquipmentStatus}
                        onChange={(e) => setNewEquipmentStatus(e.target.value)}
                    />
                    <button className="blue-button" onClick={handleCreateEquipment}>{t('Create Equipment')}</button>
                </div>
                <div className="measurement-buttons">
                    <button className="blue-button" onClick={handleStartMeasurement}>{t('Start Measurement')}</button>
                    <button className="blue-button" onClick={handleStopMeasurement}>{t('Stop Measurement')}</button>
                </div>
                {message && <p className="message">{message}</p>}
                <table className="equipment-table">
                    <thead>
                        <tr>
                            <th>{t('Name')}</th>
                            <th>{t('Status')}</th>
                            <th>{t('Actions')}</th>
                        </tr>
                    </thead>
                    <tbody>
                        {filteredEquipment.map((item) => (
                            <tr key={item.id}>
                                <td>{item.name}</td>
                                <td>{item.status}</td>
                                <td>
                                    <button className="blue-button" onClick={() => handleViewMeasurements(item.id)}>{t('Measurements')}</button>
                                    <button className="blue-button" onClick={() => handleDeleteEquipment(item.id)}>{t('Delete')}</button>
                                </td>
                            </tr>
                        ))}
                    </tbody>
                </table>
            </div>
        </div>
    );
};

export default Equipment;
