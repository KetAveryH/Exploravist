import React from 'react'
import { Fragment } from 'react'
import { Link } from "react-router-dom";
import NavLogo from '../assets/nav-logo.svg'
import '../styles/Navbar.css'

const Navbar = () => {
  return (
    <Fragment>
      <nav className='navbar'>
        <Link to='/' className='navbar_title'><img className='nav_logo' src={NavLogo} alt='ExploraVist' /></Link>
        <div className='nav_links'>
          <Link to='/updates' className='nav_link'>Updates</Link>
          <Link to='/contact' className='nav_link'>Contact</Link>
        </div>
			</nav>
    </Fragment>
  )
}

export default Navbar