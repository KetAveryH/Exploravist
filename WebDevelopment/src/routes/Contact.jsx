import React from 'react'
import { Fragment } from 'react'
import Navbar from '../components/Navbar'
import Footer from '../components/Footer'
import '../styles/Contact.css'

const Contact = () => {
  return (
    <Fragment>
        <Navbar/>
          <main className='contact'>
            <section className='contact_hero'>
              <h1 className='contact_header'>Contact Us!</h1>
              <p className='contact_paragraph'>Please send us an email if you want to test a device for free, are interested in buying one later on or have any other questions. We will actually send you one for free to test! </p>
            </section>
          </main>
        <Footer/>
    </Fragment>
  )
}

export default Contact