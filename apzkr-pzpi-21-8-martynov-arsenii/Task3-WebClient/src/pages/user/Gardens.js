import React, { useEffect, useState } from 'react';
import FullScreenImage from './components/FullScreenImage';
import './Gardens.css';

//const Gardens = () => {
//    const [gardens, setGardens] = useState([]);

//    useEffect(() => {
//        fetchGardens();
//    }, []);

//    const fetchGardens = async () => {
//        try {
//            const response = await fetch('https://localhost:7077/api/gardens');
//            const data = await response.json();
//            setGardens(data);
//        } catch (error) {
//            console.error('Ошибка при получении садиков:', error);
//        }
//    };

//    return (
//        <div className="gardens-container">
//            <FullScreenImage />
//            <div className="gardens-content">
//                <h1>Welcome to Gardens</h1>
//                <table className="gardens-table">
//                    <thead>
//                        <tr>
//                            <th>Name</th>
//                            <th>Location</th>
//                            <th>Director</th>
//                            <th>Email</th>
//                            <th>Phone</th>
//                        </tr>
//                    </thead>
//                    <tbody>
//                        {gardens.map((garden) => (
//                            <tr key={garden.id}>
//                                <td>{garden.name}</td>
//                                <td>{garden.location}</td>
//                                <td>{garden.director}</td>
//                                <td>{garden.email}</td>
//                                <td>{garden.phone}</td>
//                            </tr>
//                        ))}
//                    </tbody>
//                </table>
//            </div>
//        </div>
//    );
//};

//export default Gardens;


/*import React, { useEffect, useState } from 'react';*/
import { useNavigate } from 'react-router-dom';
/*import FullScreenImage from './components/FullScreenImage';*/
import './Gardens.css';

//const Gardens = () => {
//    const [gardens, setGardens] = useState([]);
//    const navigate = useNavigate();

//    useEffect(() => {
//        fetchGardens();
//    }, []);

//    const fetchGardens = async () => {
//        try {
//            const response = await fetch('https://localhost:7077/api/gardens');
//            const data = await response.json();
//            setGardens(data);
//        } catch (error) {
//            console.error('Ошибка при получении садиков:', error);
//        }
//    };

//    const handleViewRooms = (gardenId) => {
//        navigate(`/gardens/${gardenId}/rooms`);
//    };

//    return (
//        <div className="gardens-container">
//            <FullScreenImage />
//            <div className="gardens-content">
//                <h1>Welcome to Gardens</h1>
//                <table className="gardens-table">
//                    <thead>
//                        <tr>
//                            <th>Name</th>
//                            <th>Location</th>
//                            <th>Director</th>
//                            <th>Email</th>
//                            <th>Phone</th>
//                            <th>Actions</th>
//                        </tr>
//                    </thead>
//                    <tbody>
//                        {gardens.map((garden) => (
//                            <tr key={garden.id}>
//                                <td>{garden.name}</td>
//                                <td>{garden.location}</td>
//                                <td>{garden.director}</td>
//                                <td>{garden.email}</td>
//                                <td>{garden.phone}</td>
//                                <td>
//                                    <button onClick={() => handleViewRooms(garden.id)}>Rooms</button>
//                                </td>
//                            </tr>
//                        ))}
//                    </tbody>
//                </table>
//            </div>
//        </div>
//    );
//};

//export default Gardens;


import { useTranslation } from 'react-i18next';


//const Gardens = () => {
//    const { t } = useTranslation();
//    const [gardens, setGardens] = useState([]);
//    const [searchTerm, setSearchTerm] = useState('');
//    const [locationFilter, setLocationFilter] = useState('');
//    const navigate = useNavigate();

//    useEffect(() => {
//        fetchGardens();
//    }, []);

//    const fetchGardens = async () => {
//        try {
//            const response = await fetch('https://localhost:7077/api/gardens');
//            const data = await response.json();
//            setGardens(data);
//        } catch (error) {
//            console.error('Ошибка при получении садиков:', error);
//        }
//    };

//    const handleViewRooms = (gardenId) => {
//        navigate(`/gardens/${gardenId}/rooms`);
//    };
//    const handleSearch = (e) => {
//        setSearchTerm(e.target.value);
//    };
//    const handleLocationFilter = (e) => {
//        setLocationFilter(e.target.value);
//    };
//    const filteredGardens = gardens.filter(garden =>
//        garden.name.toLowerCase().includes(searchTerm.toLowerCase()) &&
//        garden.location.toLowerCase().includes(locationFilter.toLowerCase())
//    );
//    const handleUserSettings = () => {
//        navigate(`/user/settings`);
//    };

//    //return (
//    //    <div className="gardens-container">
//    //        <FullScreenImage />
//    //        <div className="gardens-content">
//    //            <h1>{t('Welcome to Gardens')}</h1>
//    //            <table className="gardens-table">
//    //                <thead>
//    //                    <tr>
//    //                        <th>{t('Name')}</th>
//    //                        <th>{t('Location')}</th>
//    //                        <th>{t('Director')}</th>
//    //                        <th>{t('Email')}</th>
//    //                        <th>{t('Phone')}</th>
//    //                        <th>{t('Actions')}</th>
//    //                    </tr>
//    //                </thead>
//    //                <tbody>
//    //                    {gardens.map((garden) => (
//    //                        <tr key={garden.id}>
//    //                            <td>{garden.name}</td>
//    //                            <td>{garden.location}</td>
//    //                            <td>{garden.director}</td>
//    //                            <td>{garden.email}</td>
//    //                            <td>{garden.phone}</td>
//    //                            <td>
//    //                                <button onClick={() => handleViewRooms(garden.id)}>{t('Rooms')}</button>
//    //                            </td>
//    //                        </tr>
//    //                    ))}
//    //                </tbody>
//    //            </table>
//    //        </div>
//    //    </div>
//    //);
//    return (
//        <div className="gardens-container">
//            <FullScreenImage />
//            <div className="gardens-content">
//                <h1>{t('Welcome to Gardens')}</h1>
//                <input
//                    type="text"
//                    placeholder={t('Search by name')}
//                    value={searchTerm}
//                    onChange={handleSearch}
//                    className="search-input"
//                />
//                <input
//                    type="text"
//                    placeholder={t('Filter by location')}
//                    value={locationFilter}
//                    onChange={handleLocationFilter}
//                    className="location-input"
//                />
                
//                <table className="gardens-table">
//                    <thead>
//                        <tr>
//                            <th>{t('Name')}</th>
//                            <th>{t('Location')}</th>
//                            <th>{t('Director')}</th>
//                            <th>{t('Email')}</th>
//                            <th>{t('Phone')}</th>
//                            <th>{t('Actions')}</th>
//                        </tr>
//                    </thead>
//                    <tbody>
//                        {filteredGardens.map((garden) => (
//                            <tr key={garden.id}>
//                                <td>{garden.name}</td>
//                                <td>{garden.location}</td>
//                                <td>{garden.director}</td>
//                                <td>{garden.email}</td>
//                                <td>{garden.phone}</td>
//                                <td>
//                                    <button onClick={() => handleViewRooms(garden.id)}>{t('Rooms')}</button>
//                                </td>
//                            </tr>
//                        ))}
//                    </tbody>
//                </table>
//            </div>
//        </div>
//    );
//};

//export default Gardens;
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