class Controllable {
	public:
		Controllable(){};
		virtual void handleMouseMovement(int x1, int y1, int x2, int y2) = 0;
		virtual void moveForwards() = 0;
		virtual void moveBackwards() = 0;
		virtual void moveLeft() = 0;
		virtual void moveRight() = 0;
		virtual void moveUp() = 0;
		virtual void moveDown() = 0;
};