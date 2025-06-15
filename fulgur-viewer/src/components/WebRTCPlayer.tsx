import { useEffect, useRef } from "react";

export default function WebRTCPlayer() {
  const videoRef = useRef<HTMLVideoElement>(null);
  const pcRef = useRef<RTCPeerConnection | null>(null);
  const reconnectTimer = useRef<number | null>(null);

  useEffect(() => {
    async function start() {
      if (pcRef.current) {
        pcRef.current.ontrack = null;
        pcRef.current.oniceconnectionstatechange = null;
        pcRef.current.close();
      }
      const pc = new RTCPeerConnection({
        iceServers: [],
        iceCandidatePoolSize: 1,
      });
      pcRef.current = pc;

      pc.addTransceiver("video", { direction: "recvonly" });
      pc.ontrack = (e) => {
        if (videoRef.current) {
          videoRef.current.srcObject = e.streams[0];
          videoRef.current.play().catch(() => {});
        }
      };
      pc.oniceconnectionstatechange = () => {
        const state = pc.iceConnectionState;
        console.log("ICE state:", state);
        if (state === "disconnected" || state === "failed") {
          reconnectTimer.current = window.setTimeout(start, 1000);
        }
      };

      const offer = await pc.createOffer();
      await pc.setLocalDescription(offer);
      await new Promise<void>((resolve) => {
        pc.onicecandidate = (ev) => {
          if (!ev.candidate) resolve();
        };
      });

      const res = await fetch("http://fulgur.local:8889/cam/whep", {
        method: "POST",
        mode: "cors",
        headers: { "Content-Type": "application/sdp" },
        body: pc.localDescription!.sdp,
      });
      if (!res.ok) {
        console.error("WHEP failed", res.status, await res.text());
        return;
      }

      const answer = await res.text();
      await pc.setRemoteDescription({ type: "answer", sdp: answer });
    }

    start().catch(console.error);

    return () => {
      pcRef.current?.close();
      if (reconnectTimer.current !== null) {
        clearTimeout(reconnectTimer.current);
      }
    };
  }, []);

  return (
    <video
      ref={videoRef}
      autoPlay
      playsInline
      muted
      className="absolute top-0 left-0 z-20 w-screen h-screen bg-transparent object-cover"
    />
  );
}
