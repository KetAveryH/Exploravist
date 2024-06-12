import React from 'react'
import { Fragment, useState } from 'react'
import Navbar from '../components/Navbar'
import Footer from '../components/Footer'
import { Mail } from 'lucide-react'
import '../styles/Contact.css'

const Contact = () => {
  const [copied, setCopied] = useState(false);

  const handleCopyEmail = () => {
    navigator.clipboard.writeText('dquaye@hmc.edu')
      .then(() => {
        setCopied(true);
        setTimeout(() => setCopied(false), 1500);
      })
      .catch(err => {
        console.error('Failed to copy: ', err);
      });
  };

  return (
    <Fragment>
        <Navbar/>
          <main className='contact'>
            <section className='contact_hero'>
              <h1 className='contact_header'>Contact Us!</h1>
              <p className='contact_paragraph'>Please send us an email if you want to test a device for free, are interested in buying one later on or have any other questions. We will actually send you one for free to test! </p>
              <div className='contact_link' onClick={handleCopyEmail}>
                <Mail className='contact_mail_icon' size={30}/>
                <p className='contact_mail_address'>dquaye@hmc.edu</p>
              </div>
              {copied && <p className='contact_copied_notification'>Email address copied to clipboard!</p>}
            </section>
          </main>
        <Footer/>
    </Fragment>
  )
}

export default Contact