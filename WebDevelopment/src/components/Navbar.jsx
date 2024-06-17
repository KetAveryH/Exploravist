import React from 'react';
import { Fragment, useState, useEffect } from 'react'
import { Link } from "react-router-dom";
import NavLogo from '../assets/nav-logo.svg';
import '../styles/Navbar.css';

const Navbar = () => {
  const [isSticky, setSticky] = useState(false);

  const handleScroll = () => {
    if (window.scrollY > 50) {
      setSticky(true);
    } else {
      setSticky(false);
    }
  };

  useEffect(() => {
    window.addEventListener('scroll', handleScroll);
    return () => {
      window.removeEventListener('scroll', handleScroll);
    };
  }, []);

  return (
    <Fragment>
      <nav className={`navbar ${isSticky ? 'sticky' : ''}`}>
        <Link to='/' className='navbar_title'>
          <img className='nav_logo' src={NavLogo} alt='ExploraVist' />
        </Link>
        <div className='nav_links'>
          <Link to='/contact' className='nav_link'>Contact</Link>
          <Link to='/updates' className='nav_link'>Updates</Link>
        </div>
      </nav>
    </Fragment>
  );
};

export default Navbar;