import { VideoOff } from "lucide-react";
import { TVNoise } from "./TVNoise";
import WebRTCPlayer from "./WebRTCPlayer";

export const Stream = () => {
  return (
    <div className="flex flex-col items-center justify-center h-screen">
      <WebRTCPlayer />
      <TVNoise />

      <div className="z-10 flex flex-col items-center justify-center gap-8 bg-[rgba(var(--color-fulgur-blue-dark-rgb),0.7)] rounded py-8 px-16">
        <VideoOff size={128} />

        <div className="z-10 flex flex-col items-center justify-center">
          <p className="flex items-center gap-2 text-lg text-fulgur-gray text-center">
            The stream from{" "}
            <span className="sansation-bold text-fulgur-blue">Fulgur</span> is
            currently offline.
          </p>
        </div>
      </div>
    </div>
  );
};
