import React from 'react'
import { Fragment } from 'react'
import { Link } from "react-router-dom";
import '../styles/Navbar.css'

const Navbar = () => {
  return (
    <Fragment>
      <section className='navbar_gradient'>
        <div className='navbar_gradient_bar_1'/>
        <div className='navbar_gradient_bar_2'/>
        <div className='navbar_gradient_bar_3'/>
      </section>
      <nav className='navbar'>
        <Link to='/' className='navbar_title'>ExploraVist</Link>
				<ul className='navbar_nav'> 
          <Link to='/updates' className='nav_link'>Updates</Link>
          <Link to='/contact' className='nav_link'>Contact</Link>
        </ul>
			</nav>
    </Fragment>
  )
}

export default Navbar