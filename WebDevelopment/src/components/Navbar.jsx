import React , { Fragment, useState, useEffect } from 'react';
import { Link } from "react-router-dom";
import { Menu, SquareX } from 'lucide-react';
import { motion } from 'framer-motion'
import NavLogo from '../assets/nav-logo.svg';
import '../styles/Navbar.css';

const Navbar = () => {
  const [isSticky, setSticky] = useState(false);
  const [isMobileMenu, setMobileMenu] = useState(false);
  const [isMobileMenuVisible, setMobileMenuVisible] = useState(false);


  const handleResize = () => {
    if (window.innerWidth <= 700) {
      setMobileMenu(true);
      setMobileMenuVisible(false);
    } else {
      setMobileMenu(false);
      setMobileMenuVisible(false);
    }
  }

  const handleScroll = () => {
    if (window.scrollY > 50) setSticky(true);
    else setSticky(false);
  }

  const toggleMobileMenu = () => {
    setMobileMenuVisible(!isMobileMenuVisible);
  }


  useEffect(() => {
    handleResize();

    window.addEventListener('resize', handleResize);
    window.addEventListener('scroll', handleScroll);
    return () => {
      window.removeEventListener('resize', handleResize);
      window.removeEventListener('scroll', handleScroll);
    }
  }, [])

  return (
    <Fragment>
      <nav className={`navbar ${isSticky ? 'sticky' : ''}`}>
        <Link to='/' className='navbar_title'>
          <img className='nav_logo' src={NavLogo} alt='ExploraVist' />
        </Link>
        <div className='nav_links'>
          {!isMobileMenu && 
            <div>
              <Link to='/contact' className='nav_link'>Contact</Link>
              <Link to='/updates' className='nav_link'>Updates</Link>
            </div>
          }
          {isMobileMenu &&
            <div>
              <button className='nav_link' onClick={toggleMobileMenu}><Menu/></button>
              {isMobileMenuVisible &&
              <motion.div
                className='nav_mobile_menu_dropdown'
                initial={{ y: '-100%' }}
                animate={{ y: 0 }}
                exit={{ y: '-100%' }}
                transition={{ duration: 0.5 }}
              >
                <div className='nav_mobile_menu'>
                  <div className='nav_mobile_menu_x'>
                    <button className='nav_mobile_menu_x_btn' onClick={toggleMobileMenu}><SquareX className='square' size={70}/></button>
                  </div>
                  <div className='nav_mobile_menu_links'>
                    <p className='nav_mobile_menu_title'>Menu</p>
                    <Link to='/' className='nav_mobile_menu_link'>Home</Link>
                    <Link to='/updates' className='nav_mobile_menu_link'>Updates</Link>
                    <Link to='/contact' className='nav_mobile_menu_link'>Contact</Link>
                  </div>
                </div>
              </motion.div>
              }
            </div>
          }
        </div>
      </nav>
    </Fragment>
  );
};

export default Navbar;