import React from 'react'
import { Fragment } from 'react'
import { Link } from "react-router-dom";

const Navbar = () => {
  return (
    <Fragment>
        <Link to='/'>Home</Link>
        <Link to='/updates'>Updates</Link>
        <Link to='/contact'>Contact</Link>
    </Fragment>
  )
}

export default Navbar