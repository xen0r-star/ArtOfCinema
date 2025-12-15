/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        primary: {
          DEFAULT: '#e11d48', // Rose-600
          foreground: '#ffffff',
        },
        secondary: {
          DEFAULT: '#1f2937', // Gray-800
          foreground: '#ffffff',
        },
        background: '#030712', // Gray-950
        surface: '#111827', // Gray-900
      },
    },
  },
  plugins: [],
}

