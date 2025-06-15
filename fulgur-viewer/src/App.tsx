import { NatsConnection, StringCodec, connect } from "nats.ws";
import { useEffect, useState } from "react";
import { FullScreen, useFullScreenHandle } from "react-full-screen";
import { Battery } from "./components/Battery";
import { Controller } from "./components/Controller";
import { Signal } from "./components/Signal";
import { Stream } from "./components/Stream";
import { ToggleFullscreen } from "./components/ToggleFullscreen";
import { useControllerState } from "./store/controller";
import { useFulgurInfos } from "./store/fulgur";

function App() {
  const handle = useFullScreenHandle();
  const setControllerState = useControllerState((state) => state.setState);
  const setFulgurInfos = useFulgurInfos((state) => state.setInfos);
  const [nats, setNats] = useState<NatsConnection>();

  useEffect(() => {
    (async () => {
      const nc = await connect({
        servers: ["ws://localhost:9222"],
      });

      if (!nc) {
        console.error("Failed to connect to NATS");
        return;
      }
      console.log("Connected to NATS.");

      const controllerState = nc?.subscribe("CONTROLLER.STATE");
      const sc = StringCodec();

      if (!controllerState) {
        console.error("Failed to subscribe to CONTROLLER.STATE");
        return;
      }
      console.log("Subscribed to CONTROLLER.STATE");
      setNats(nc);

      (async () => {
        for await (const m of controllerState) {
          setControllerState(JSON.parse(sc.decode(m.data)));
        }
        console.log("Subscription closed.");
      })();

      const fulgurInfos = nc?.subscribe("FULGUR.INFOS");

      if (!fulgurInfos) {
        console.error("Failed to subscribe to FULGUR.INFOS");
        return;
      }

      console.log("Subscribed to FULGUR.INFOS");

      (async () => {
        for await (const m of fulgurInfos) {
          setFulgurInfos(JSON.parse(sc.decode(m.data)));
        }
        console.log("Subscription closed.");
      })();
    })();

    return () => {
      nats?.drain();
      console.log("Connection to NATS closed.");
    };
  }, []);
  // TODO set isConnect to controller
  return (
    <FullScreen handle={handle} className="bg-fulgur-blue-dark">
      {/* {nats ? (
        <h1>Connected to {nats?.getServer()}</h1>
      ) : (
        <h1>Connecting to NATS...</h1>
      )} */}
      <Stream />

      <div className="absolute z-50 flex flex-col items-start justify-end gap-3 bottom-3 left-3">
        <Signal />
        <Battery batteryLevel={100} isCharging={true} />
        <Controller />
      </div>

      <div className="absolute z-50 flex items-end justify-end gap-3 bottom-3 right-3">
        <ToggleFullscreen
          onClick={() => (handle.active ? handle.exit() : handle.enter())}
          isFullscreen={handle.active}
        />
      </div>
    </FullScreen>
  );
}

export default App;
