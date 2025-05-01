export const TVNoise = () => {
  return (
    <>
      <div id="tv-noise" className="z-0"></div>
      <svg className="w-0 h-0">
        <filter id="noise">
          <feTurbulence id="turbulence">
            <animate
              attributeName="baseFrequency"
              dur="50s"
              values="0.9 0.9;0.8 0.8; 0.9 0.9"
              repeatCount="indefinite"
            ></animate>
          </feTurbulence>
          <feDisplacementMap in="SourceGraphic" scale="60"></feDisplacementMap>
        </filter>
      </svg>
    </>
  );
};
