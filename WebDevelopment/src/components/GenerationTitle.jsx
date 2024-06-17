import React from 'react'
import  {Fragment } from 'react'
import '../styles/GenerationTitle.css'

const GenerationTitle = (props) => {
  return (
    <Fragment>
      <header className='generationtitle'>
        <p className='generationtitle_num'>Gen {props.gen_num}:</p>
        <p className='generationtitle_date'>({props.gen_date})</p>
        <p className='generationtitle_title'>{props.gen_title}</p>
      </header>
    </Fragment>
  )
}

export default GenerationTitle