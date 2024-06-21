import React from 'react'
import ReactDOM from 'react-dom/client'
import { RouterProvider, createBrowserRouter } from 'react-router-dom'
import Home from './routes/Home.jsx'
import Updates from './routes/Updates.jsx'
import Contact from './routes/Contact.jsx'
import './index.css'
import Error404 from './routes/Error404.jsx'

const router = createBrowserRouter([
  {path: '/', element: <Home/>},
  {path: '/updates', element: <Updates/>},
  {path: '/contact', element: <Contact/>},
  {path: '*', element: <Error404/>}
])


ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <RouterProvider router = {router} />
  </React.StrictMode>,
)
