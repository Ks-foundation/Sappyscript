import "react";

namespace Components {
    class GreetingComponent {
        constructor(props) {
            this.props = props;
        }

        render() {
            return (
                <div>
                    <h1>Hello, {this.props.name}!</h1>
                    <p>Welcome to the world of Sappyscript and React!</p>
                </div>
            );
        }
    }
}

function App() {
    return (
        <div>
            <h1>My React App</h1>
            <Components.GreetingComponent name="Sappy" />
        </div>
    );
}

log("Rendering App component...");
ReactDOM.render(
    <App />,
    document.getElementById('root')
);
