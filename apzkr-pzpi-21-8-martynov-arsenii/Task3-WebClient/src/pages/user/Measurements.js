import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import FullScreenImage from './components/FullScreenImage';
import './Measurements.css';

//const Measurements = () => {
//    const { equipmentId } = useParams();
//    const [measurements, setMeasurements] = useState([]);

//    useEffect(() => {
//        fetchMeasurements();
//    }, []);

//    const fetchMeasurements = async () => {
//        try {
//            const response = await fetch(`https://localhost:7077/api/equipment/${equipmentId}/measurements`);
//            const data = await response.json();
//            setMeasurements(data);
//        } catch (error) {
//            console.error('Ошибка при получении измерений:', error);
//        }
//    };

//    return (
//        <div className="measurements-container">
//            <FullScreenImage />
//            <div className="measurements-content">
//                <h1>Measurements for Equipment</h1>
//                <table className="measurements-table">
//                    <thead>
//                        <tr>
//                            <th>Measurement Type</th>
//                            <th>Value</th>
//                        </tr>
//                    </thead>
//                    <tbody>
//                        {measurements.map((measurement) => (
//                            <tr key={measurement.id}>
//                                <td>{measurement.measurementType}</td>
//                                <td>{measurement.value}</td>
//                            </tr>
//                        ))}
//                    </tbody>
//                </table>
//            </div>
//        </div>
//    );
//};

//export default Measurements;



import { useTranslation } from 'react-i18next';


//const Measurements = () => {
//    const { t } = useTranslation();
//    const { equipmentId } = useParams();
//    const [measurements, setMeasurements] = useState([]);
//    const [searchTerm, setSearchTerm] = useState('');
//    const [valueFilter, setValueFilter] = useState('');

//    useEffect(() => {
//        fetchMeasurements();
//    }, []);

//    const fetchMeasurements = async () => {
//        try {
//            const response = await fetch(`https://localhost:7077/api/equipment/${equipmentId}/measurements`);
//            const data = await response.json();
//            setMeasurements(data);
//        } catch (error) {
//            console.error('Ошибка при получении измерений:', error);
//        }
//    };

//    const handleSearch = (e) => {
//        setSearchTerm(e.target.value);
//    };

//    const handleValueFilter = (e) => {
//        setValueFilter(e.target.value);
//    };

//    const filteredMeasurements = measurements.filter(measurement =>
//        measurement.measurementType.toLowerCase().includes(searchTerm.toLowerCase()) &&
//        (!valueFilter || measurement.value.toString().includes(valueFilter))
//    );

//    return (
//        <div className="measurements-container">
//            <FullScreenImage />
//            <div className="measurements-content">
//                <h1>{t('Measurements for Equipment')}</h1>
//                <input
//                    type="text"
//                    placeholder={t('Search by type')}
//                    value={searchTerm}
//                    onChange={handleSearch}
//                    className="search-input"
//                />
//                <input
//                    type="text"
//                    placeholder={t('Filter by value')}
//                    value={valueFilter}
//                    onChange={handleValueFilter}
//                    className="value-input"
//                />
//                <table className="measurements-table">
//                    <thead>
//                        <tr>
//                            <th>{t('Measurement Type')}</th>
//                            <th>{t('Value')}</th>
//                        </tr>
//                    </thead>
//                    <tbody>
//                        {filteredMeasurements.map((measurement) => (
//                            <tr key={measurement.id}>
//                                <td>{measurement.measurementType}</td>
//                                <td>{measurement.value}</td>
//                            </tr>
//                        ))}
//                    </tbody>
//                </table>
//            </div>
//        </div>
//    );
//};

//export default Measurements;




const Measurements = () => {
    const { t } = useTranslation();
    const { equipmentId } = useParams();
    const [measurements, setMeasurements] = useState([]);
    const [searchTerm, setSearchTerm] = useState('');
    const [valueFilter, setValueFilter] = useState('');

    useEffect(() => {
        fetchMeasurements();
    }, []);

    const fetchMeasurements = async () => {
        try {
            const response = await fetch(`https://localhost:7077/api/equipment/${equipmentId}/measurements`);
            const data = await response.json();
            setMeasurements(data);
        } catch (error) {
            console.error('Ошибка при получении измерений:', error);
        }
    };

    const handleSearch = (e) => {
        setSearchTerm(e.target.value);
    };

    const handleValueFilter = (e) => {
        setValueFilter(e.target.value);
    };

    const filteredMeasurements = measurements.filter(measurement =>
        measurement.measurementType.toLowerCase().includes(searchTerm.toLowerCase()) &&
        (!valueFilter || measurement.value.toString().includes(valueFilter))
    );

    return (
        <div className="measurements-container">
            <FullScreenImage />
            <div className="measurements-content">
                <h1>{t('Measurements for Equipment')}</h1>
                <input
                    type="text"
                    placeholder={t('Search by type')}
                    value={searchTerm}
                    onChange={handleSearch}
                    className="search-input"
                />
                <input
                    type="text"
                    placeholder={t('Filter by value')}
                    value={valueFilter}
                    onChange={handleValueFilter}
                    className="value-input"
                />
                <table className="measurements-table">
                    <thead>
                        <tr>
                            <th>{t('Measurement Type')}</th>
                            <th>{t('Value')}</th>
                        </tr>
                    </thead>
                    <tbody>
                        {filteredMeasurements.map((measurement) => (
                            <tr key={measurement.id}>
                                <td>{measurement.measurementType}</td>
                                <td>{measurement.value}</td>
                            </tr>
                        ))}
                    </tbody>
                </table>
            </div>
        </div>
    );
};

export default Measurements;
