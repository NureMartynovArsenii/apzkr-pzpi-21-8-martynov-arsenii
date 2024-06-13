import React, { useState, useEffect } from 'react';
import FullScreenImage from './components/FullScreenImage';
import AdminGardens from './AdminGardens';
import AdminUsers from './AdminUsers';
import AdminRooms from './AdminRooms';
import AdminEquipment from './AdminEquipment';
import AdminMeasurements from './AdminMeasurements';
import AdminBackup from './AdminBackup';
import './AdminPage.css';

const AdminPage = () => {
    const [status, setStatus] = useState("Unknown");

    useEffect(() => {
        checkStatus();
    }, []);

    const getAuthToken = () => {
        return localStorage.getItem('token');
    };

    const startMeasurement = async () => {
        try {
            const response = await fetch('https://localhost:7077/api/admin/start', {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${getAuthToken()}`,
                    'Content-Type': 'application/json'
                }
            });
            if (response.ok) {
                setStatus("On");
            } else {
                console.error('Error starting measurement:', response.statusText);
            }
        } catch (error) {
            console.error('Error starting measurement:', error);
        }
    };

    const stopMeasurement = async () => {
        try {
            const response = await fetch('https://localhost:7077/api/admin/stop', {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${getAuthToken()}`,
                    'Content-Type': 'application/json'
                }
            });
            if (response.ok) {
                setStatus("Off");
            } else {
                console.error('Error stopping measurement:', response.statusText);
            }
        } catch (error) {
            console.error('Error stopping measurement:', error);
        }
    };

    const checkStatus = async () => {
        try {
            const response = await fetch('https://localhost:7077/api/admin/status', {
                headers: {
                    'Authorization': `Bearer ${getAuthToken()}`,
                    'Content-Type': 'application/json'
                }
            });
            if (response.ok) {
                const data = await response.json();
                setStatus(data.isMeasuring ? "On" : "Off");
            } else {
                console.error('Error fetching status:', response.statusText);
            }
        } catch (error) {
            console.error('Error fetching status:', error);
        }
    };

    return (
        <div>
            <FullScreenImage />
            <div className="admin-page-container">
                <h1>Welcome to Admin Page</h1>
                <div className="measurement-controls">
                    <button onClick={startMeasurement}>Start Measurement</button>
                    <button onClick={stopMeasurement}>Stop Measurement</button>
                    <p>Status: {status === "On" ? "Measurement is active" : "Measurement is turned off"}</p>
                </div>
                <AdminGardens />
                <AdminUsers />
                <AdminRooms />
                <AdminEquipment />
                <AdminMeasurements />
                <AdminBackup />
            </div>
        </div>
    );
};

export default AdminPage;
