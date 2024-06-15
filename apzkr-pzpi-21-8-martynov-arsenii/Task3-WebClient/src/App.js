import React from 'react';
import { BrowserRouter as Router, Route, Routes, Navigate } from 'react-router-dom';
import FullScreenImage from './components/FullScreenImage';
import Menu from './components/Menu';
import Registration from './Registration';
import Authorization from './Authorization';
import Gardens from './Gardens';
import AdminPage from './AdminPage';
import Rooms from './Rooms';
import Equipment from './Equipment'; 
import Measurements from './Measurements';
import './i18n'
import UserSettings from './UserSettings';
import Logout from './Logout';
/*import { BrowserRouter as *//*Router*//* *//*Route*//* Routes, Navigate } from 'react-router-dom';*/
import './App.css';


const PrivateRoute = ({ children }) => {
    const token = localStorage.getItem('token');
    return token ? children : <Navigate to="/admin/login" />;
    return token ? children : <Navigate to="/authorization" />;
};

function App() {
    return (
        <Router>
            <Menu />
            <Routes>
                <Route path="/" element={<FullScreenImage />} />
                <Route path="/registration" element={<Registration />} />
                <Route path="/authorization" element={<Authorization />} />
                <Route path="/admin/login" element={<Authorization />} />
                <Route path="/adminpage" element={
                    <PrivateRoute>
                        <AdminPage />
                    </PrivateRoute>
                } />
                <Route path="/gardens/:gardenId" element={<Gardens />} />
                <Route path="/gardens" element={<Gardens />} />
                <Route path="/gardens/:gardenId/rooms" element={<Rooms />} />
                <Route path="/rooms/:roomId/equipment" element={<Equipment />} />
                <Route path="/equipment/:equipmentId/measurements" element={<Measurements />} />
                <Route path="/user/settings" element={<UserSettings />} />
                <Route path="/logout" element={<Logout />} />
            </Routes>
        </Router>
    );
}

export default App;

