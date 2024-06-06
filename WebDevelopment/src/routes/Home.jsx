import React from 'react'
import { Fragment } from 'react'
import Navbar from '../components/Navbar'
import HomeLogo from '../assets/home-logo.svg'
import '../styles/Home.css';

const Home = () => {
  return (
    <Fragment>
        <Navbar />
        <section className='home_hero'>
          <img className='home_logo' src={HomeLogo} alt='Home Logo' />
        </section>
        
    </Fragment>
  )
}

export default Home