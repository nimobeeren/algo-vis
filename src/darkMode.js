// Adapted from: https://joshwcomeau.com/gatsby/dark-mode/

function getInitialColorMode() {
  const persistedColorPreference = window.localStorage.getItem('color-mode');
  const hasPersistedPreference = typeof persistedColorPreference === 'string';

  // If the user has explicitly chosen light or dark,
  // let's use it. Otherwise, this value will be null.
  if (hasPersistedPreference) {
    return persistedColorPreference;
  }

  // If they haven't been explicit, let's check the media
  // query
  const mql = window.matchMedia('(prefers-color-scheme: dark)');
  const hasMediaQueryPreference = typeof mql.matches === 'boolean';
  if (hasMediaQueryPreference) {
    return mql.matches ? 'dark' : 'light';
  }

  // If they are using a browser/OS that doesn't support
  // color themes, let's default to 'light'.
  return 'light';
}

const colorMode = getInitialColorMode();

const root = document.documentElement;

// Get dark and light color values from CSS variables
const computedStyle = getComputedStyle(root);
const light =computedStyle.getPropertyValue('--color-light'); 
const dark = computedStyle.getPropertyValue('--color-dark');

if (colorMode === 'dark') {
  // If in dark mode, simply swap the light and dark colors
  root.style.setProperty('--color-light', dark);
  root.style.setProperty('--color-dark', light);
}

root.style.setProperty('--initial-color-mode', colorMode);
