import { Expand, Shrink } from "lucide-react";

interface ToggleFullscreenProps {
  onClick: () => void;
  isFullscreen?: boolean;
}

export const ToggleFullscreen = ({
  onClick,
  isFullscreen,
}: ToggleFullscreenProps) => {
  return (
    <button
      className="flex justify-center items-center size-12 bg-[rgba(var(--color-fulgur-blue-dark-rgb),0.7)] text-white rounded"
      onClick={onClick}
    >
      {isFullscreen ? <Shrink size={28} /> : <Expand size={28} />}
    </button>
  );
};
