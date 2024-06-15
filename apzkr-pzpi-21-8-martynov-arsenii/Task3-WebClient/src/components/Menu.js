import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import './Menu.css';
import accountIcon from './account-icon.png';
import { useTranslation } from 'react-i18next';
import { useNavigate } from 'react-router-dom';
// Вкажіть правильний шлях до іконки

const Menu = () => {
    const [isMenuOpen, setIsMenuOpen] = useState(false);
    const { t, i18n } = useTranslation();
    const navigate = useNavigate();
    const token = localStorage.getItem('token');

    const toggleMenu = () => {
        setIsMenuOpen(!isMenuOpen);
    };

    const closeMenu = () => {
        setIsMenuOpen(false);
    };

    const changeLanguage = (lng) => {
        i18n.changeLanguage(lng);
    };

    const handleLogout = () => {
        localStorage.removeItem('token');
        navigate('/');
    };

    return (
        <div className="menu-container">
            <div className="menu-left">
                <button className="menu-button" onClick={() => changeLanguage('ua')}>{t('Ukrainian')}</button>
                <button className="menu-button" onClick={() => changeLanguage('en')}>{t('English')}</button>
            </div>
            <div className="menu-center">
                {t('ChildClimaCare')}
            </div>
            <div className="menu-right">
                <img src={accountIcon} className="account-icon" alt="Account Icon" onClick={toggleMenu} />
                {isMenuOpen && (
                    <div className="dropdown-menu">
                        <Link to="/" onClick={closeMenu}>{t('Main')}</Link>
                        {!token && (
                            <>
                                <Link to="/registration" onClick={closeMenu}>{t('Registration')}</Link>
                                <Link to="/authorization" onClick={closeMenu}>{t('Authorization')}</Link>
                            </>
                        )}
                        {token && (
                            <>
                                <Link to="/user/settings" onClick={closeMenu}>{t('My Account')}</Link>
                                <button onClick={handleLogout}>{t('Logout')}</button>
                            </>
                        )}
                        <button onClick={closeMenu}>Close</button>
                    </div>
                )}
            </div>
        </div>
    );
};

export default Menu;
