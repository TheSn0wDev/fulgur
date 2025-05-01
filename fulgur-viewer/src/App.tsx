import { FullScreen, useFullScreenHandle } from "react-full-screen";
import { Battery } from "./components/Battery";
import { Controller } from "./components/Controller";
import { Signal } from "./components/Signal";
import { Stream } from "./components/Stream";
import { ToggleFullscreen } from "./components/ToggleFullscreen";

function App() {
  const handle = useFullScreenHandle();

  return (
    <FullScreen handle={handle} className="bg-fulgur-blue-dark">
      <Stream />

      <div className="absolute bottom-3 left-3 flex flex-col gap-3 justify-end items-start z-50">
        <Signal ping={95} />
        <Battery batteryLevel={100} isCharging={true} />
        <Controller batteryLevel={100} isConnected={true} />
      </div>

      <div className="absolute bottom-3 right-3 flex gap-3 justify-end items-end z-50">
        <ToggleFullscreen
          onClick={() => (handle.active ? handle.exit() : handle.enter())}
        />
      </div>
    </FullScreen>
  );
}

export default App;
